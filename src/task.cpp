#include "task.hpp"
#include "mqtt.hpp"

static localization_coordinates coordinates;
static car_obd_data car_data;

static String car_id_global;

static bool error = false;
static char* message = "";
static uint16_t try_connect_to_network = 0;
static bool deinit = true;

typedef struct{
    state_t state;
}state_machine_t;

struct Button {
	const uint8_t PIN;
	bool pressed;
};

Button button1 = {35, false};

unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void IRAM_ATTR isr() {
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
          button1.pressed = !button1.pressed;
          last_button_time = button_time;
    }
}

void IRAM_ATTR handleBootButton() {
    clear_storage();
    sleep(100);
    ESP.restart();
}

state_machine_t MyMachine;
typedef int (*sm_handler_t)(state_machine_t* ev);


static int sm_handler_state_SLEEP(state_machine_t* ev)
{
    if (button1.pressed) {
      deinit = false;
      ev->state = INITIAL;
      return 1;
	  }
    else
    {
      if (!deinit)
      {
        display_deinit();
        disconnect_MQTT();
        wifi_deinit();
        bluetooth_deinit();
        gps_deinit();
        digitalWrite(32, LOW);
        deinit = true;
      }
      car_data.speed = 0;
      car_data.rpm = 0;
      car_data.fuel_level = 0;
      coordinates.geographic_X = 0;
      coordinates.geographic_Y = 0;
      ev->state = SLEEP_STATE;
    }
    return 1;
}


static int sm_handler_state_INITIAL(state_machine_t* ev)
{
    setup_display();
    initialization_perform();
    setup_gps();
    String ssid = get_actual_ssid();
    String password = get_actual_password();
    String car_id = get_actual_car_id();
    car_id_global = car_id;
    print("Initializing");
    if(!elm_connect()) 
      sleep(200);
    setup_wifi(ssid.c_str(), password.c_str());
    mqtt_init("192.168.1.146", "mario", "Mario123", car_id_global.c_str());
    ev->state = RECEIVE_STATE;
    return 1;
}
static int sm_handler_state_RECEIVE_STATE(state_machine_t* ev)
{
    error = false;
    if (!button1.pressed)
    {
        ev->state=SLEEP_STATE;
        return 1;
    }
    track_localization();
    coordinates.geographic_X = get_latitude();
    coordinates.geographic_Y = get_longitude();
    car_data.rpm = (uint32_t)get_car_value(RPM) * 30;
    car_data.speed = get_car_value(SPEED);
    car_data.fuel_level = get_car_value(FUEL);

    if (car_data.speed < 0 || car_data.rpm < 0 || car_data.fuel_level < 0)
    {
      message = "Receive data failed!";
      error = true;
      ev->state = DISPLAY_STATE;
      delay(100);
    }

    error = false;
    ev->state = SEND_STATE;
    delay(100);
    return 1;
}
static int sm_handler_state_DISPLAY_STATE(state_machine_t* ev)
{
    if (error)
    {
      print(message);
      digitalWrite(32, LOW);
      ev->state = RECEIVE_STATE;
      delay(100);
      return 1;
    }
    show_data(car_data.rpm, car_data.speed, car_data.fuel_level, coordinates.geographic_X, coordinates.geographic_Y);
    ev->state = RECEIVE_STATE;
    return 1;
}
static int sm_handler_state_SEND_STATE(state_machine_t* ev)
{
  if (!button1.pressed){
      ev->state=SLEEP_STATE;
      return 1;
  }
  if(connect(100)){
    if (!connect_MQTT()){
      try_connect_to_network++;
      if(try_connect_to_network == 3){
        message = "MQTT connection failed!";
        error = true;
        try_connect_to_network = 0;
        ev->state = DISPLAY_STATE;
      }
      return 1;
    }
    digitalWrite(32, HIGH);
    if(mqtt_send(car_id_global, car_data.speed, car_data.rpm,
      car_data.fuel_level, coordinates.geographic_X,coordinates.geographic_Y)){
      error = false;
      delay(100);
      digitalWrite(32, LOW);
      ev->state = DISPLAY_STATE;
      return 1;
    }
  }
 
  try_connect_to_network++;
  print("Attempting to connect");
  if(try_connect_to_network == 3)
  {
    message = "Connection to WiFi failed!";
    error = true;
    try_connect_to_network = 0;
    ev->state = DISPLAY_STATE;
  }
  return 1;
}
sm_handler_t handlers[] = 
{
    sm_handler_state_SLEEP,
    sm_handler_state_INITIAL,
    sm_handler_state_RECEIVE_STATE,
    sm_handler_state_DISPLAY_STATE,
    sm_handler_state_SEND_STATE
};

int sm_event_handler(state_machine_t* ev)
{
    return handlers[ev->state](ev);
}


void task_setup() 
{
    pinMode(button1.PIN, INPUT_PULLUP);
    pinMode(32, OUTPUT);
    pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);
	  attachInterrupt(button1.PIN, isr, FALLING);
    attachInterrupt(BOOT_BUTTON_PIN, handleBootButton, FALLING);
}

void task_loop() {
  sm_event_handler(&MyMachine);
  delay(10);
}

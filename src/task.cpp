#include "task.hpp"
#include "mqtt.hpp"

Elm myELM327 = Elm(1);
localization_coordinates coordinates;


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

state_machine_t MyMachine;
typedef int (*sm_handler_t)(state_machine_t* ev);


static int sm_handler_state_INITIAL(state_machine_t* ev)
{
    if (button1.pressed) {
      ev->state = RECEIVE_STATE;
      Serial.println("Clicked");
      return 1;
	  }
    else
      myELM327.diagnostic_datas.car_speed = 0;
      myELM327.diagnostic_datas.car_rpm = 0;
      myELM327.diagnostic_datas.fuel_level = 0;
      ev->state = INITIAL;
    return 1;
}
static int sm_handler_state_RECEIVE_STATE(state_machine_t* ev)
{
    if (!button1.pressed)
    {
        ev->state=TURN_OFF_STATE;
        return 1;
    }
    digitalWrite(32, HIGH);
    // print("Receiving datas: ");
    // myELM327.set_speed(myELM327.get_speed());
    // myELM327.set_rpm(myELM327.get_rpm());
    // myELM327.set_fuel(myELM327.get_fuel());
    // print("Localization");
    track_localization();
    coordinates.geographic_X = get_latitude();
    coordinates.geographic_Y = get_longitude();
    myELM327.set_speed(7);
    myELM327.set_rpm(12);
    myELM327.set_fuel(9);
    ev->state = SEND_STATE;
    delay(100);
    // digitalWrite(32, LOW);
    return 1;
}
static int sm_handler_state_DISPLAY_STATE(state_machine_t* ev)
{
    show_data(myELM327.diagnostic_datas.car_rpm, myELM327.diagnostic_datas.car_speed, myELM327.diagnostic_datas.fuel_level, coordinates.geographic_X, coordinates.geographic_Y);
    delay(100);
    ev->state = RECEIVE_STATE;
    return 1;
}
static int sm_handler_state_SEND_STATE(state_machine_t* ev)
{
  print("Connect to Network");
  if(connect(100))
  {
    // print("Connected");
    // delay(400);
    if (!connect_MQTT())
    {
      // print("Dupa");
      return 1;
    }
    // print("Connection Succesfull!");
    digitalWrite(32, HIGH);
    if(mqtt_send(
      myELM327.diagnostic_datas.car_speed, myELM327.diagnostic_datas.car_rpm,
      myELM327.diagnostic_datas.fuel_level, coordinates.geographic_X,
      coordinates.geographic_Y)){
      delay(100);
      digitalWrite(32, LOW);
      ev->state = DISPLAY_STATE;
      return 1;
    }
  }
  digitalWrite(32, LOW);
  print("Connection Failed!");
  delay(100);
  return 1;
}
static int sm_handler_state_TURN_OFF_STATE(state_machine_t* ev)
{
  clear_display();
  ev->state=INITIAL;
  digitalWrite(32, LOW);
  return 1;

}
sm_handler_t handlers[] = {sm_handler_state_INITIAL, sm_handler_state_RECEIVE_STATE, sm_handler_state_DISPLAY_STATE, sm_handler_state_SEND_STATE, sm_handler_state_TURN_OFF_STATE};

int sm_event_handler(state_machine_t* ev)
{
    return handlers[ev->state](ev);
}


void task_setup(const char* ssid, const char* password) 
{
    Serial.begin(115200);
    pinMode(button1.PIN, INPUT_PULLUP);
    pinMode(32, OUTPUT);
	  attachInterrupt(button1.PIN, isr, FALLING);
    setup_display();
    setup_gps();  // Nowe
    // print("Connecting to ELM:");
    // myELM327.init_elm();


    setup_wifi(ssid, password);
    mqtt_init("192.168.1.146", "mario", "Mario123", "2"); //Zmienione
    
}

void task_loop() {
  sm_event_handler(&MyMachine);
  delay(10); // this speeds up the simulation
}

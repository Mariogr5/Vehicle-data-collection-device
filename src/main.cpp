// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <iostream>
// #include "Elm.hpp"
// #include <cstdio>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Elm myELM327 = Elm(1);

// typedef struct
// {
//   uint16_t rpm;
//   uint16_t car_speed;
//   uint16_t fuel_level;
// } car_diagnostic_datas;

// car_diagnostic_datas car_datas;

// typedef enum {INITIAL, RECEIVE_STATE, DISPLAY_STATE, SEND_STATE, TURN_OFF_STATE} state_t;

// typedef struct{
//     state_t state;
// }state_machine_t;


// struct Button {
// 	const uint8_t PIN;
// 	uint32_t numberKeyPresses;
// 	bool pressed;
// };

// Button button1 = {35, 0, false};

// //variables to keep track of the timing of recent interrupts
// unsigned long button_time = 0;  
// unsigned long last_button_time = 0; 

// void IRAM_ATTR isr() {
//     button_time = millis();
//     if (button_time - last_button_time > 250)
//     {
//           button1.numberKeyPresses++;
//           button1.pressed = !button1.pressed;
//           last_button_time = button_time;
//     }
// }

// state_machine_t MyMachine;
// typedef int (*sm_handler_t)(state_machine_t* ev);


// static int sm_handler_state_INITIAL(state_machine_t* ev)
// {
//     if (button1.pressed) {
//       ev->state = RECEIVE_STATE;
//       return 1;
// 	  }
//     else
//       car_datas.car_speed = myELM327.get_car_value("speed");
//       car_datas.rpm = 0;
//       car_datas.fuel_level = 0;
//       ev->state = INITIAL;
//     return 1;
// }
// static int sm_handler_state_RECEIVE_STATE(state_machine_t* ev)
// {
//   if (!button1.pressed)
//   {
//       ev->state=TURN_OFF_STATE;
//       return 1;
//   }
//   digitalWrite(32, HIGH);
//   car_datas.car_speed++;
//   car_datas.rpm++;
//   car_datas.fuel_level++;
//   ev->state = DISPLAY_STATE;
//   delay(100);
//   digitalWrite(32, LOW);
//   return 1;
// }
// static int sm_handler_state_DISPLAY_STATE(state_machine_t* ev)
// {
//     char speed[100];
//     char fuel[100];
//     char rpm[100];
//     sprintf(speed, "Speed: %d", car_datas.car_speed);
//     sprintf(rpm, "Rpm: %d", car_datas.rpm);
//     sprintf(fuel, "Fuel: %d", car_datas.fuel_level);

//     display.clearDisplay();
//     display.setCursor(0, 10);
//     display.println(speed);
//     display.setCursor(0, 20);
//     display.println(rpm);
//     display.setCursor(0, 30);
//     display.println(fuel);
//     display.display();
//     delay(100);
//     ev->state = RECEIVE_STATE;
    
//     return 1;
// }
// static int sm_handler_state_SEND_STATE(state_machine_t* ev)
// {
  
// }
// static int sm_handler_state_TURN_OFF_STATE(state_machine_t* ev)
// {
//   display.clearDisplay();
//   ev->state=INITIAL;
//   digitalWrite(32, LOW);
//   display.display();
//   return 1;

// }
// sm_handler_t handlers[] = {sm_handler_state_INITIAL, sm_handler_state_RECEIVE_STATE, sm_handler_state_DISPLAY_STATE, sm_handler_state_SEND_STATE, sm_handler_state_TURN_OFF_STATE};

// int sm_event_handler(state_machine_t* ev)
// {
//     return handlers[ev->state](ev);
// }


// void setup() {
//     Serial.begin(115200);
//     pinMode(button1.PIN, INPUT_PULLUP);
//     pinMode(32, OUTPUT);
// 	  attachInterrupt(button1.PIN, isr, FALLING);

//     if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
//       Serial.println(F("SSD1306 allocation failed"));
//       for(;;);
//     }
//     delay(2000);
//     display.clearDisplay();

//     display.setTextSize(1);
//     display.setTextColor(WHITE);
//     display.setCursor(0, 10);
//     // Display static text
//     // display.println("Dupa: ");
//     display.display(); 
// }

// void loop() {
//   sm_event_handler(&MyMachine);
//   // put your main code here, to run repeatedly:
//   delay(10); // this speeds up the simulation
// }

#include "task.hpp"

void setup()
{
  task_setup("dad", "adad");
}

void loop()
{
  task_loop();
}
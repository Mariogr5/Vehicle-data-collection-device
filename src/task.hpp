#ifndef task_hpp
#define task_hpp

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <iostream>
#include "Elm.hpp"
#include "display.hpp"
#include "wifi.hpp"
#include "gps.hpp"
#include <cstdio>


typedef enum {INITIAL, RECEIVE_STATE, DISPLAY_STATE, SEND_STATE, TURN_OFF_STATE} state_t;


void task_setup(const char* ssid, const char* password);
void task_loop();


#endif
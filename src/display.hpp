#ifndef display_hpp
#define display_hpp

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


void setup_display();
void clear_display();
void print(char* message);
void show_data(uint16_t rpm, uint16_t speed, uint16_t fuel, float latitude, float longitude);

#endif
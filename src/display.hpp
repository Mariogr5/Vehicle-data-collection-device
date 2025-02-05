#ifndef display_hpp
#define display_hpp

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


void setup_display();
void display_deinit();
void clear_display();
void print(char* message);
void show_data(uint32_t rpm, float speed, float fuel, float latitude, float longitude);

#endif
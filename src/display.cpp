#include "display.hpp"

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup_display()
{
    if(!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }
    delay(1000);
    OLED.clearDisplay();

    OLED.setTextSize(1);
    OLED.setTextColor(WHITE);
    OLED.setCursor(0, 10);
    OLED.display(); 
}

void clear_display()
{
    OLED.clearDisplay();
    OLED.display();
}

void show_data(uint16_t rpm, uint16_t speed, uint16_t fuel)
{
    char speed_buffer[100];
    char fuel_buffer[100];
    char rpm_buffer[100];
    sprintf(speed_buffer, "Speed: %d", speed);
    sprintf(rpm_buffer, "Rpm: %d", rpm);
    sprintf(fuel_buffer, "Fuel: %d", fuel);

    OLED.clearDisplay();
    OLED.setCursor(0, 10);
    OLED.println(speed);
    OLED.setCursor(0, 20);
    OLED.println(rpm);
    OLED.setCursor(0, 30);
    OLED.println(fuel);
    OLED.display();
    delay(100);
}
void print(char* message)
{
    OLED.clearDisplay();
    OLED.setCursor(0, 20);
    OLED.println(message);
    OLED.display();
}

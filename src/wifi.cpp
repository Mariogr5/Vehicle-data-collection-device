#include "wifi.hpp"


void setup_wifi(const char* ssid, const char* password)
{
    WiFi.begin(ssid, password);
}

bool connect(uint32_t timeout)
{
    uint32_t start_time = millis();
    uint32_t current_time = 0;
    while(WiFi.status() != WL_CONNECTED){
        current_time = millis();

        if(current_time - start_time > timeout)
        {
            return false;
        }

        Serial.print(".");
        delay(100);
    }
    
    return true;
}
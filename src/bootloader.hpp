#include "bluetooth.hpp"
#include "display.hpp"
#include "WiFi.h"
#include "NVS_flash.hpp"

typedef struct 
{
    const char* car_id;
    const char* ssid;
    const char* password;
} init_data_frame;


void init_bluetooth();
void send_info(String message);
String get_message();
void set_car_id(const char* car_id);
void set_ssid(const char* ssid);
void set_password(const char* password);
String get_actual_car_id();
String get_actual_ssid();
String get_actual_password();

void bootloader_perform();

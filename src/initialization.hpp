#include "bluetooth.hpp"
#include "display.hpp"
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
String get_actual_car_id();
String get_actual_ssid();
String get_actual_password();

void initialization_perform();

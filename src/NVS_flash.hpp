#include "Preferences.h"

void init_NVS();
void close_NVS();
void clear_storage();
String get_car_id();
String get_ssid();
String get_password();
void save_car_id(String car_id);
void save_ssid(String ssid);
void save_password(String password);
bool is_connection_settings_empty();
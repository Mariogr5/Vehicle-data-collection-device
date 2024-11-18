#include "NVS_flash.hpp"

Preferences preferences;

void init_NVS()
{
    preferences.begin("settings", false);
}

void close_NVS()
{
    preferences.end();
}

void clear_storage()
{
    init_NVS();
    preferences.clear();
    // preferences.remove("car_id");
    // preferences.remove("ssid");
    // preferences.remove("password");
    close_NVS();
}


String get_car_id()
{
    return preferences.getString("car_id", "NULL");
}
String get_ssid()
{
    return preferences.getString("ssid", "NULL");
}
String get_password()
{
    return preferences.getString("password", "NULL");
}

void save_car_id(String car_id)
{
    preferences.putString("car_id", car_id);
}
void save_ssid(String ssid)
{
    preferences.putString("ssid", ssid);
}
void save_password(String password)
{
    preferences.putString("password", password);
}

bool is_connection_settings_empty()
{
    // String car_id = get_car_id();
    // String ssid = get_ssid();
    // String password = get_password();
    
    if (preferences.isKey("car_id") && preferences.isKey("ssid") && preferences.isKey("password"))
    {
        if(get_car_id() != "NULL" && get_ssid() != "NULL" && get_password() != "NULL")
            return false;
    }
    return true;
}
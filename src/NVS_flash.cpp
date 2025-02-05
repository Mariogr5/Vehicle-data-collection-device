#include "NVS_flash.hpp"

Preferences preferences;


static String trimSpecialCharacters(String input)
{
  while(input.length() > 0 && (input[input.length() - 1] == '\r' || input[input.length() - 1] == '\n'))
  {
    input.remove(input.length() - 1);
  }
  return input;
}


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
    close_NVS();
}


String get_car_id()
{
    return trimSpecialCharacters(preferences.getString("car_id", "NULL"));
}
String get_ssid()
{
    return trimSpecialCharacters(preferences.getString("ssid", "NULL"));
}
String get_password()
{
    return trimSpecialCharacters(preferences.getString("password", "NULL"));
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
    if (preferences.isKey("car_id") && preferences.isKey("ssid") && preferences.isKey("password"))
    {
        if(get_car_id() != "NULL" && get_ssid() != "NULL" && get_password() != "NULL")
            return false;
    }
    return true;
}
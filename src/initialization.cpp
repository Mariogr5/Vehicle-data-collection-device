#include "initialization.hpp"
static init_data_frame init_data;

void init_bluetooth()
{
    setup_bluetooth_initialization();
}

void send_info(String message)
{
    send_bluetooth_command(message);
}

String get_user_input()
{
    String user_input;
    user_input = get_message();
    return user_input;
}

String get_actual_car_id()
{
    String value;
    init_NVS();
    value =  get_car_id();
    close_NVS();
    delay(100);
    return value;
}
String get_actual_ssid()
{
    String value;
    init_NVS();
    value =  get_ssid();
    close_NVS();
    delay(100);
    return value;
}

String get_actual_password()
{
    String value;
    init_NVS();
    value =  get_password();
    close_NVS();
    delay(100);
    return value;
}

void initialization_perform()
{
    init_NVS();
    if (!is_connection_settings_empty())
    {
        close_NVS();
        return;
    }
    init_bluetooth();
    print("Enter data via Bluetooth\n");
    while (!check_connection()){}
    send_info("Enter Car Id\n");
    String car_id = get_user_input();
    while(!check_connection()){}
    send_info("Enter WiFi ssid\n");
    String ssid = get_user_input();
    while(!check_connection()){}
    send_info("Enter WiFi password\n");
    String password = get_user_input();
    save_car_id(car_id);
    save_ssid(ssid);
    save_password(password);
    bluetooth_deinit();
    close_NVS();
    print("zROBIONE");
}
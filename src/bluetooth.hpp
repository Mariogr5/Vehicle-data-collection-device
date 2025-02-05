#include "BluetoothSerial.h"
#include <string>

#ifndef bluetooth_hpp
#define bluetooth_hpp

    extern BluetoothSerial SerialBT;

    void setup_bluetooth();
    void setup_bluetooth_initialization();
    void bluetooth_deinit();
    bool bluetooth_connect(uint32_t timeout);
    void send_bluetooth_command(String command);
    String get_message();
    bool check_connection();

#endif

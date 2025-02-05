#include "bluetooth.hpp"

   BluetoothSerial SerialBT;
    void setup_bluetooth() 
    {
        SerialBT.begin("car_device",true);
        SerialBT.setPin("1234");
    }

    bool bluetooth_connect(uint32_t timeout)
    {
        uint32_t time = 0;
        while(!SerialBT.connect("ELMULATOR"))
        {
            time++;
            if(time >= timeout)
            {
                return false;
            }
        }
        return true;
    }

    void setup_bluetooth_initialization() 
    {
        SerialBT.begin("car_device_bootload_2", false);
    }

    void bluetooth_deinit()
    {
        SerialBT.end();
    }

    void send_bluetooth_command(String command)
    {
        uint8_t buf[command.length()];

        memcpy(buf,command.c_str(),command.length());
        SerialBT.write(buf, command.length());
        delay(1);
    }

    bool check_connection()
    {
        return SerialBT.connected();
    }

    String get_message()
    {
        String incomingMessage;
        while(true)
        {
            if (SerialBT.available()) {
                incomingMessage = SerialBT.readStringUntil('\n');
                break;
            }
        }
        return incomingMessage;
    }

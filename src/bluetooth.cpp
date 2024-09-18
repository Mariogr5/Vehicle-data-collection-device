#include "bluetooth.hpp"

   BluetoothSerial SerialBT;
    void setup_bluetooth(int id) 
    {
        SerialBT.begin("esp_test" + char(id),true);
        SerialBT.setPin("1234");
    }


    void send_bluetooth_command(String PID)
    {
        uint8_t buf[PID.length()];

        memcpy(buf,PID.c_str(),PID.length());
        SerialBT.write(buf, PID.length());
        delay(1);
    }

    String receive_bluetooth_datas()
    {
        String message = "";
        uint16_t i = 0;
        while (SerialBT.available()) {
            String part = SerialBT.readStringUntil('\n');
            if (part != ">")
                message += part;
            i++;                           
            Serial.println(part);
            if (i == 3) {
            Serial.println(message);
            }
        }
        if (message != "")
            return message;
        return "00 00";
    }
    

    String receive_bluetooth_datas_test()
    {
        String message = "";
        uint16_t i = 0;
        while(1)
        {
            if(SerialBT.available()){
            message += SerialBT.readStringUntil('\n');
            Serial.println(message);
            break;
            }
        }

        if (message != "")
            return message;
        return "00 00";
    }

    bool check_connection()
    {
        return SerialBT.connected();
    }


    
    void setup_bluetooth_test(int id) 
    {
        SerialBT.begin("final_test" + char(id));
        SerialBT.setPin("1234");
    }

#include "bluetooth.hpp"

   BluetoothSerial SerialBT;
    void setup_bluetooth(int id) 
    {
        SerialBT.begin("esp_test" + char(id),true);
        SerialBT.setPin("1234");

        if (!SerialBT.connect("OBDII"))
        {
            while(1);
        }
    }

    void setup_bluetooth_bootloader() 
    {
        SerialBT.begin("car_device_bootload", false);
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

    // String receive_bluetooth_datas()
    // {
    //     String message = "";
    //     uint16_t i = 0;
    //     while (SerialBT.available()) {
    //         String part = SerialBT.readStringUntil('\n');
    //         if (part != ">")
    //             message += part;
    //         i++;                           
    //         Serial.println(part);
    //         if (i == 3) {
    //         Serial.println(message);
    //         }
    //     }
    //     if (message != "")
    //         return message;
    //     return "00 00";
    // }
    

    // String receive_bluetooth_datas_test()
    // {
    //     String message = "";
    //     uint16_t i = 0;
    //     while(1)
    //     {
    //         if(SerialBT.available()){
    //         message += SerialBT.readStringUntil('\n');
    //         Serial.println(message);
    //         break;
    //         }
    //     }

    //     if (message != "")
    //         return message;
    //     return "00 00";
    // }

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
                incomingMessage = SerialBT.readStringUntil('\n');  // Odczytujemy dane jako string
                Serial.print("Received message: ");
                Serial.println(incomingMessage);
                break;
            }
        }
        return incomingMessage;
    }
    
    // void setup_bluetooth_test(int id) 
    // {
    //     SerialBT.begin("final_test" + char(id));
    //     SerialBT.setPin("1234");
    // }

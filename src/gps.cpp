#include "gps.hpp"

HardwareSerial neogps(1);
TinyGPSPlus gps;

static localization_coordinates _coordinates;

void setup_gps()
{
    neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
}


// static void get_coordinates()
// {
//     if (gps.location.isValid() == 1)
//     {
//         // Serial.println(gps.location.lat());
//         // Serial.println(gps.location.lng());
//         _coordinates.geographic_X = gps.location.lat();
//         _coordinates.geographic_Y = gps.location.lng();
//     }
//     else
//     {
//         _coordinates.geographic_X = 0;
//         _coordinates.geographic_Y = 0;
//     }
// }

void track_localization()
    {
        while (neogps.available() > 0) {
        gps.encode(neogps.read());  // Dekodujemy dane z GPS
        
        // Sprawdzamy, czy mamy poprawne dane lokalizacji
        if (gps.location.isUpdated()) {
        // Serial.print("Latitude: ");
        // Serial.println(gps.location.lat(), 6);  // Wypisujemy szerokość geograficzną z dokładnością do 6 miejsc po przecinku
        // Serial.print("Longitude: ");
        // Serial.println(gps.location.lng(), 6);  // Wypisujemy długość geograficzną z dokładnością do 6 miejsc po przecinku
        _coordinates.geographic_Y = gps.location.lng();
        _coordinates.geographic_X = gps.location.lat();
        break;
        // Serial.println("--------------------------");
        }
    }

        // boolean newData = false;
        // for (unsigned long start = millis(); millis() - start < 1000;)
        // {
        //   while (neogps.available())
        //   {
        //     if (gps.encode(neogps.read()))
        //     {
        //       newData = true;
        //     }
        //   }
        // }

        // if(newData == true)
        // {
        //   newData = false;
        //   get_coordinates();
        // }
        // else
        // {
        //     _coordinates.geographic_X = 0;
        //     _coordinates.geographic_Y = 0;
        // }
    }

double get_latitude()
{
    return _coordinates.geographic_X;
}

double get_longitude()
{
    return _coordinates.geographic_Y;
}
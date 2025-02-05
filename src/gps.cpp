#include "gps.hpp"

HardwareSerial neogps(1);
TinyGPSPlus gps;

static localization_coordinates _coordinates;


void setup_gps()
{
    neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void gps_deinit()
{
    neogps.end();
    pinMode(RXD2, INPUT);
    pinMode(TXD2, INPUT);
}


void track_localization()
{
    while (neogps.available() > 0) {
    gps.encode(neogps.read());
    
    if (gps.location.isUpdated()) {
    _coordinates.geographic_Y = gps.location.lng();
    _coordinates.geographic_X = gps.location.lat();
    break;
    }
}
}

double get_latitude()
{
    return _coordinates.geographic_X;
}

double get_longitude()
{
    return _coordinates.geographic_Y;
}
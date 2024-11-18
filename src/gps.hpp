#ifndef gps_hpp
#define gps_hpp

#include <TinyGPSPlus.h>

#define RXD2 16
#define TXD2 17
#define GPS_BAUD 9600

struct localization_coordinates
{
    double geographic_X;
    double geographic_Y;
};

void setup_gps();
double get_latitude();
double get_longitude();
void track_localization();

#endif
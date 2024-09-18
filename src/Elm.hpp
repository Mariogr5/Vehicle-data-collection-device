#include <string>
#include "bluetooth.hpp"
#include "ELMduino.h"

#ifndef Elm_hpp
#define Elm_hpp

// #define CAR_SPEED "010D"
// #define CAR_RPM   "010C"
// #define FUEL_LEVEL "012F"

class Elm
{
    private:
    int car_id;

    struct car_datas
    {
        int car_speed;
        float car_rpm;
        bool if_drive;
        bool if_idling;
        bool if_car_run;
        float fuel_level;
        float odometer;
        bool if_car_errors;
        double geographic_latitude;
        double geographic_longitude; 

    };

    public:

    car_datas diagnostic_datas;

    Elm(int Car_id);

    void init_elm();
    // float get_rpm();
    // float get_speed();
    float get_car_value(String value_to_get);

    void set_speed(float value);

    void set_fuel(float value);

    void set_rpm(float value);

    float get_speed();

    float get_fuel();
    
    float get_rpm();

};

#endif
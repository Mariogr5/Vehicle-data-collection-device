#include <string>
#include "bluetooth.hpp"
#include "display.hpp"
#include "ELMduino.h"

#ifndef Elm_hpp
#define Elm_hpp

struct car_obd_data
{
    float speed;
    uint32_t rpm;
    float fuel_level;
};

enum CarValueType {
    RPM,
    SPEED,
    FUEL,
};

bool elm_connect();
float get_car_value(CarValueType value_to_get);

#endif
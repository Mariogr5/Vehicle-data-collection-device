#include "Elm.hpp"

ELM327 userELM327;

Elm::Elm(int Car_id) : car_id(Car_id){}


void Elm:: init_elm()
{
  setup_bluetooth(car_id);

  if (!userELM327.begin(SerialBT, true, 2000))
  {
    Serial.println("Couldn't connect to OBD scanner - Phase 2");
    while (1);
  }

  Serial.println("Connected to ELM327");
}


float Elm::get_car_value(String value_to_get)
{
  float temp_value;
  uint32_t value;
  
  if (value_to_get == "rpm")
    temp_value = userELM327.rpm();
  else if(value_to_get == "speed")
    temp_value = userELM327.kph();
  else if(value_to_get == "fuel")
    temp_value = userELM327.fuelLevel();
  else
    temp_value = userELM327.kph();

  if (userELM327.nb_rx_state == ELM_SUCCESS)
  {
    value = (uint32_t)temp_value;
    Serial.print("RPM: "); Serial.println(value);
  }
  else if (userELM327.nb_rx_state != ELM_GETTING_MSG)
    userELM327.printError();
    return 0;

  return value;
}

void Elm:: set_speed(float value)
{
  diagnostic_datas.car_speed = value;
}
void Elm::set_fuel(float value)
{
  diagnostic_datas.fuel_level = value;
}
void Elm::set_rpm(float value)
{
  diagnostic_datas.car_rpm = value;
}
float Elm::get_speed()
{
  return get_car_value("speed");
}
float Elm::get_fuel()
{
   return get_car_value("fuel");
}
float Elm::get_rpm()
{
   return get_car_value("rpm");
}


// float Elm:: get_rpm()
// {
//   uint32_t rpm;
//   float tempRPM = userELM327.rpm();

//   if (userELM327.nb_rx_state == ELM_SUCCESS)
//   {
//     rpm = (uint32_t)tempRPM;
//     Serial.print("RPM: "); Serial.println(rpm);
//   }
//   else if (userELM327.nb_rx_state != ELM_GETTING_MSG)
//     userELM327.printError();
//     return 0;
//   return rpm;
// }

// float Elm:: get_speed()
// {
//   uint32_t speed;
//   float tempRPM = userELM327.rpm();

// }


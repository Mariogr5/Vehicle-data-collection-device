#include "Elm.hpp"

ELM327 userELM327;

static bool check_the_data_transfer_state()
{
  if (userELM327.nb_rx_state == ELM_SUCCESS)
  {
    return true;
  }
  else if (userELM327.nb_rx_state != ELM_GETTING_MSG)
  {
    userELM327.printError();
    return false;
  }
  else
  {
    return false;
  }
}

bool elm_connect()
{
  setup_bluetooth();
  if(!bluetooth_connect(5000))
  {
    print("Couldn't connect to OBD scanner - Phase 1");
    return false;
  }

  if (!userELM327.begin(SerialBT, false, 5000))
  {
    print("Couldn't connect to OBD scanner - Phase 2");
    return false;
  }
  print("Connected to ELM327");
  return true;
}

float get_car_value(CarValueType value_to_get)
{
  float value = 0;
  do
  {
  switch (value_to_get)
    {
        case SPEED:
            value = userELM327.kph();
            break;
        case RPM:
            value = userELM327.rpm();
            break;
        case FUEL:
            value = userELM327.fuelLevel();
            break;
        default:
            value = userELM327.kph();
            break;
    }
    if (userELM327.nb_rx_state != ELM_GETTING_MSG && userELM327.nb_rx_state != ELM_SUCCESS)
    {
      userELM327.printError();
      sleep(30);
      return -1;
    }
  }while(userELM327.nb_rx_state != ELM_SUCCESS);

  return value;
}


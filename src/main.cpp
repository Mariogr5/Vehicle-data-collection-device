
// #include "task.hpp"
#include "bootloader.hpp"
void setup()
{
  // clear_storage();
  Serial.begin(115200);
  bootloader_perform();
  Serial.println(get_actual_car_id());
  Serial.println(get_actual_ssid());
  Serial.println(get_actual_password());
  // task_setup("Mleko", "Marekgra5");
}

void loop()
{
  // task_loop();
  // Serial.print("Daty: ");
  // init_NVS();
  // Serial.println(get_actual_car_id());
  // // close_NVS();
  // Serial.println(get_actual_ssid());
  // Serial.println(get_actual_password());
  // delay(1000);
}
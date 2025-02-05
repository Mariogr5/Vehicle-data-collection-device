#ifndef mqtt_hpp
#define mqtt_hpp

#include "wifi.hpp"
#include "PubSubClient.h"
#include <ArduinoJson.h>

bool connect_MQTT();
void disconnect_MQTT();

bool mqtt_send(String car_id, float speed, uint32_t rpm, float fuel, double latitude, double longitude);
void mqtt_init(const char* server, const char* username, const char* password, const char* Id);

#endif
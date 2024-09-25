#ifndef mqtt_hpp
#define mqtt_hpp

#include "wifi.hpp"
#include "PubSubClient.h"
#include <ArduinoJson.h>

bool connect_MQTT();
bool mqtt_send(float speed, float rpm, float fuel);

void set_mqtt_server(const char* server);

void set_topic(const char* new_topic);

void mqtt_init(const char* server, const char* username, const char* password, const char* Id);


#endif
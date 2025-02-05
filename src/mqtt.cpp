#include "mqtt.hpp"

static const char* mqtt_server = "192.168.1.146"; 

static const char* mqtt_username = "mario";
static const char* mqtt_password = "Mario123";
static const char* clientID = "2";
static const char* topic = "/home/data_with_localization";


static WiFiClient wifiClient;

static PubSubClient client(mqtt_server, 1883, wifiClient);

bool connect_MQTT(){
    return client.connect(clientID, mqtt_username, mqtt_password);
}

void disconnect_MQTT()
{
    client.disconnect();
}

bool mqtt_send(String car_id, float speed, uint32_t rpm, float fuel, double latitude, double longitude){
    StaticJsonDocument<512> doc;
    doc["car_id"] = car_id;
    doc["speed"] = speed;
    doc["fuel"] = fuel;
    doc["rpm"] = rpm;
    doc["latitude"] = latitude;
    doc["longitude"] = longitude;
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);

    return client.publish(topic, String(jsonBuffer).c_str());
}

void mqtt_init(const char* server, const char* username, const char* password, const char* Id)
{
    mqtt_server = server;
    mqtt_username = username;
    mqtt_password = password;
    clientID = Id;
}
#include "mqtt.hpp"

static const char* mqtt_server = "192.168.1.146"; 
static const char* mqtt_username = "mario";
static const char* mqtt_password = "Mario123";
static const char* clientID = "2";
static const char* topic = "/home/data_with_localization";
// static const char* topic = "/home/car_dataas";



static WiFiClient wifiClient;

static PubSubClient client(mqtt_server, 1883, wifiClient);

bool connect_MQTT(){
    return client.connect(clientID, mqtt_username, mqtt_password);
}

bool mqtt_send(float speed, float rpm, float fuel, double latitude, double longitude){
    StaticJsonDocument<512> doc;
    doc["speed"] = speed;
    doc["fuel"] = fuel;
    doc["rpm"] = rpm;
    doc["latitude"] = 51.06;  //51.06
    doc["longitude"] = 17.01; //17.01″
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);

    return client.publish(topic, String(jsonBuffer).c_str());
}
void set_topic(const char* new_topic)
{
    topic = new_topic;
}

void set_mqtt_server(const char* server)
{
    mqtt_server = server;
}

void mqtt_init(const char* server, const char* username, const char* password, const char* Id)
{
    mqtt_server = server;
    mqtt_username = username;
    mqtt_password = password;
    clientID = Id;
}
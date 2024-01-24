/*
*   MQTT Broaker
*/

#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Pablo";
const char* password = "010250@Maldini";

// MQTT Broker
const char *mqtt_broker = "public.mqtthq.com";
const char *topic = "esp32/test";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length) 
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    
    for (int i = 0; i < length; i++) 
            Serial.print((char) payload[i]);
        
    Serial.println();
    Serial.println("-----------------------");
}

void reConnect()
{
    while (!client.connected()) 
    {
        Serial.print("Connecting to MQTT broker...");
        if (client.connect("ESP32Client")) 
        {
            Serial.println("connected");
            client.subscribe(topic);
        } 
        else 
        {
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(1000);
        }
    }
}

void setup()   
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while(WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.println("Connecting to WiFi ...");
    }

    Serial.println("\nConnected to Wi-Fi!");
    Serial.print("IP address : ");
    Serial.println(WiFi.localIP());

    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    reConnect();

    client.publish(topic, "Hi EMQX I'm ESP32 ^^");
    client.subscribe(topic);
}

void loop() 
{
    if (!client.connected()) 
    {
        reConnect();
    }
    client.publish(topic, "Hello, MQTT!");
    delay(500);
}

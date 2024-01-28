/*
*   Thing Speak IoT Dashboard
*/

#include <WiFi.h>
#include "ThingSpeak.h"

WiFiClient client;
const char* ssid = "Pablo";
const char* password = "010250@Maldini";

int channelNumber = 2413824;
char *apiKey = "07CNAOBFUPFNW7DG";
char *serverName = "api.thingspeak.com";

int field1=0, field2=20, field3=5;
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

    /* Thing Speak Configurations */
    ThingSpeak.begin(client);
}

void loop() 
{
    ThingSpeak.setField(1, field1++);
    ThingSpeak.setField(2, field2--);
    ThingSpeak.setField(3, field3++);

    int status = ThingSpeak.writeFields(channelNumber, apiKey);
    if(status == 200) 
        Serial.println("Successful chanel update.");
    else
        Serial.println("Error chanel update.");

    delay(15000);
}

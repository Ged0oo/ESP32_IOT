/*
*   NTP Server
*/

#include <WiFi.h>
#include <NTPClient.h>

const char* ssid = "Pablo";
const char* password = "010250@Maldini";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int dayLightOffset = 3600;

void printLocalTime()
{
    struct tm timeInfo;
    if(!getLocalTime(&timeInfo))
    {
        Serial.println("Can't obtain time.");
        return;
    }
    Serial.println(&timeInfo, "%A, %B %d %Y %H:%M:%S");
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

    configTime(gmtOffset_sec, dayLightOffset, ntpServer);
}

void loop() 
{
    printLocalTime();
    delay(1000);
}

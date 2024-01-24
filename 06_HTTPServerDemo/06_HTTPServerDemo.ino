/*
*   NTP Server
*/

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Pablo";
const char* password = "010250@Maldini";

AsyncWebServer server(80);

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

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", "OK Route");});
    server.begin();
}

void loop() 
{

}

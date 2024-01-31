#define THINGER_SERIAL_DEBUG

#include <WiFi.h>
#include <ThingerESP32.h>

#define USERNAME "ged0oo"
#define DEVICE_ID "EME-NAGY"
#define DEVICE_CREDENTIAL "kp7bHi+_RI48R0jv"

#define SSID "Pablo"
#define SSID_PASSWORD "010250@Maldini"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int temp=25, humadity=70, con=15;
void setup() 
{
  // open serial for debugging
  Serial.begin(115200); 

  pinMode(2, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["GPIO_2"] << digitalPin(2);

  // resource output example (i.e. reading a sensor value)
    thing["millis"] >> outputValue(millis());
    thing["Temperature"] >> outputValue(temp);
    thing["humadity"] >> outputValue(humadity);
    thing["con"] >> outputValue(con);
}

void loop() 
{
    temp += (rand()%10);
    humadity += (rand()%10);
    thing.handle();
    delay(500);
}
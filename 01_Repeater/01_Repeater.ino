#include <WiFi.h>

int n = 0;
String ssid = "";
String sudo_ssid = "sudo";
String pass = "";


char ConnectionFlag = 0;
unsigned long pMillis = 0;
unsigned long cMillis = 0;
unsigned long interval = 5000;


void wifiScan(void)
{
  Serial.println("\nScan Started");
  n = WiFi.scanNetworks();
  int numNetworks = WiFi.scanComplete();

  if(n == 0) Serial.println("Not networks found");
  else 
  {
    Serial.print(n);
    Serial.println(" Network found");
  }

  Serial.println("\nEnter the no. of the network you want to connect\n");
  Serial.println("-----------------------------------");

  for (int i = 0; i < numNetworks; ++i) 
  {
      Serial.print("Network Number : ");
      Serial.println(i+1);

      Serial.print("Network name : ");
      Serial.println(WiFi.SSID(i));
      
      Serial.print("Signal strength: ");
      Serial.println(WiFi.RSSI(i));
      
      Serial.println("-----------------------------------");
      delay(100);
  }

  while (Serial.available() == 0){}
  int no_ssid = Serial.parseInt();
  wifiConnection(no_ssid);
}


void WiFi_Init(void)
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  int timeout = millis();
  while ((WiFi.status() != WL_CONNECTED) && (millis() - timeout < 8000)) 
  {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  if(WiFi.status() != WL_CONNECTED && WiFi.status() != WL_NO_SSID_AVAIL)
  {
      Serial.println("Password is not correct");
      ESP.restart();
  }
  else if(WiFi.status() != WL_CONNECTED && WiFi.status() == WL_NO_SSID_AVAIL)
  {
      Serial.println("Wifi network is not avaliable");
      ESP.restart();
  }
  else
  {
      Serial.println("\nConnected to Wi-Fi!");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      repeater_Init();
  }
}


void wifiConnection(int no_ssid)
{
    ssid = WiFi.SSID(no_ssid - 1);  

    if((WiFi.encryptionType(no_ssid - 1) != WIFI_AUTH_OPEN))
    {
        Serial.print("Enter Wi-Fi password : ");
        while (true)
        {
          while (!Serial.available()) 
          {
            // Wait for user input
          }

          pass = Serial.readString();
          pass.trim(); // Remove leading and trailing whitespace
        
          if (pass.length() >= 8) 
          {
            Serial.println();
            break; // Exit the loop if the password length is sufficient
          } 
          else 
          {
            Serial.println("Password should be at least 8 characters\n");
          }
        }
    }
    else
    {
        pass = "";
    }
}


void repeater_Init(void)
{
  WiFi.softAP(sudo_ssid, pass);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP address : ");
  Serial.println(IP);
}


void setup() 
{
  Serial.begin(115200);
  wifiScan();
  WiFi_Init();
}


void loop() 
{
  cMillis = millis();

  if ((WiFi.status() != WL_CONNECTED) &&
      (cMillis - pMillis >= interval))
      {
        ConnectionFlag = 1;
        Serial.println("Reconnecting to WiFi ...");
        WiFi.disconnect();
        WiFi.reconnect();
        pMillis = cMillis;
      }
      else if((WiFi.status() == WL_CONNECTED) &&
              (ConnectionFlag==1))
              {
                  ConnectionFlag = 0;
                  Serial.println("\nReconnected to WiFi.");
                  Serial.print("Host IP address : ");
                  Serial.println(WiFi.localIP());
                  Serial.print("Access Point IP address : ");
                  Serial.println(WiFi.softAPIP());
              }
  
}


//#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

/*
   display settings
*/
#define TFT_DC         25
#define TFT_RST        26
#define TFT_CS         27
#define TFT_MOSI      23
#define TFT_SCLK      18

// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() 
{
    // Initialize TFT display
    tft.initR(INITR_BLACKTAB); // Use the correct initialization setting for your display
    tft.setRotation(3); // Use the correct rotation for your display
    tft.fillScreen(ST7735_BLACK); // Clear the screen to black
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(2);
}

void loop() 
{
    tft.setCursor(10, 50); // Set the cursor position
    tft.print("Hello ESP32!"); // Display your message
    delay(1000); // Delay for 1 second
}
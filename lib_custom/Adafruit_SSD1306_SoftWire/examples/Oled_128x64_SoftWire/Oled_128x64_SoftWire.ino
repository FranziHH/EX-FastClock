#include <SoftWire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306_SoftWire.h>
// #include <Fonts/FreeSans9pt7b.h>
// #include "fonts/Open_Sans_Regular_9.h"

#define WIDTH 128
#define HEIGHT 64

#define OLED_RESET -1

#define sdaPin A2
#define sclPin A3

SoftWire i2c(sdaPin, sclPin);
Adafruit_SSD1306 oled(WIDTH, HEIGHT, &i2c, OLED_RESET);
  
void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //oled.cp437(true);
  //oled.setFont(&Open_Sans_Regular_9);

  // Clear the buffer
  oled.clearDisplay();
}

void loop() {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.print("Hello, time elapsed:");
  oled.setCursor(10,10);
  oled.setTextSize(2);
  oled.print(millis()/1000);
  oled.print(" s.");
  oled.display();
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Screen.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

void printMessage(String message) {
  display.clearDisplay();
  display.display();
  display.setCursor(0, 0);
  display.print(message);
  display.display();
}

void initializeOled() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  display.display();
  delay(500);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

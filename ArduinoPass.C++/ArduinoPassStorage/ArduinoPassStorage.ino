#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define STORAGE_ADDR 9

File myFile;

void setup() {
  Wire.begin(STORAGE_ADDR);
  Wire.onReceive(receiveEvent);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  if (!SD.begin(4)) {
    digitalWrite(LED_BUILTIN, LOW);
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
}

void receiveEvent(int numBytes) {
  digitalWrite(LED_BUILTIN, LOW);
  
  String content = "";
  char character;
  while (Wire.available()) {
    digitalWrite(LED_BUILTIN, HIGH);
    character = Wire.read();
    content.concat(character);
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
  }

  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    myFile.println(content);
    myFile.close();
  } else {
  }
}

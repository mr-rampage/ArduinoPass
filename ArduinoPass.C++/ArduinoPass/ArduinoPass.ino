#include "Screen.h"
#include "Flux.h"
#include "Communication.h"
#include "Storage.h"

State mode = WAITING;

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  initializeCommunication();
  initializeOled();
  if (!initializeStorage()) {
    printMessage(":(");
    while (1);
  }
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    mode = next(mode, Serial.readString());
    displayState(mode);
  }

  onButtonA(&reset);
  onButtonB(&sendText);
  onButtonC(&savePassword);
}

void reset() {
  mode = WAITING;
  displayState(mode);
}

void displayState(State currentState) {
  switch (currentState) {
    case WAITING:
      printMessage("Waiting");
      break;
    case READY:
      printMessage("Ready");
      break;
    case BUSY:
      printMessage("Busy");
      break;
    default:
      printMessage(":(");
      break;
  }
}

void sendText() {
  if (mode == READY) {
    sendPassword("Hello!");
  }
}

void savePassword() {
  if (mode == READY) {
    if (appendToFile("test.txt", "Hello, World!"))
    {
      printMessage("Saved!");
    } else {
      printMessage(":(");
    }
  }
}

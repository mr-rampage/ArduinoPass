#include "Screen.h"
#include "Flux.h"
#include "Communication.h"

State mode = WAITING;

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  initializeCommunication();
  initializeOled();
  printMessage("Waiting");
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    printMessage("Processing");
    mode = next(mode, Serial.readString());
    displayState(mode);
  }

  onButtonA(&reset);
  onButtonB(&sendText);
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
      printMessage("Bad State");
      break;
  }
}

void sendText() {
  if (mode == READY) {
    sendPassword("Hello!");
  }
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Keyboard.h"

#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5

#define RE(signal, state) (state=(state<<1)|(signal&1)&3)==1
int btnState[3];

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

typedef enum { WAITING, READY, BUSY } State;

typedef enum { NOOP, GREET, DATA } Command;

State mode = WAITING;
Command command = NOOP;
const String HANDSHAKE_GREETING = "CONNECT";
const String HANDSHAKE_RESPONSE = "OK";

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  Keyboard.begin();
  initializeButtons();
  initializeOled();
  printMessage("Waiting");
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    printMessage("Processing");
    command = adaptCommand(Serial.readString());
    State previousMode = mode;
    mode = validateCommand(mode, command);
    publishChange(previousMode, mode);
    displayState(mode);
  }
  
  if (RE(digitalRead(BUTTON_A), btnState[0])) {
    mode = WAITING;
    displayState(mode);
  }

  if (RE(digitalRead(BUTTON_B), btnState[1])) {
    sendText();
  }

  if (RE(digitalRead(BUTTON_C), btnState[2])) {

  }
}

Command adaptCommand(String unverifiedCommand) {
  unverifiedCommand.trim();
  if (unverifiedCommand == HANDSHAKE_GREETING) {
    return GREET;
  }
  return NOOP;
}

State validateCommand(State currentState, Command verifiedCommand) {
  if (verifiedCommand == GREET && currentState == WAITING) {
    return READY;
  }
  return currentState;
}

State publishChange(State previousState, State newState) {
  if (previousState == WAITING && newState == READY) {
    Serial.println(HANDSHAKE_RESPONSE);
    printMessage("ACK sent!");
  }

  return newState;
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
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void initializeButtons() {
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
}

void sendText() {
  Keyboard.println("Hello!");
}

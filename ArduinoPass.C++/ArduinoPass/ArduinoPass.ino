#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5

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
  pinMode(BUTTON_A, INPUT_PULLUP);
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
  if(!digitalRead(BUTTON_A)) {
    mode = WAITING;
    displayState(mode);
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

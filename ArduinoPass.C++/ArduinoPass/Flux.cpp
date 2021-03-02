#include "Flux.h"

typedef enum { NOOP, GREET, AUTHENTICATE, DATA } Command;

const String HANDSHAKE_GREETING = "CONNECT";
const String HANDSHAKE_RESPONSE = "OK";

Command adaptCommand(String unverifiedCommand) {
  unverifiedCommand.trim();
  if (unverifiedCommand == HANDSHAKE_GREETING) {
    return GREET;
  }
  return NOOP;
}

State validateCommand(State currentState, Command verifiedCommand) {
  if (verifiedCommand == GREET && currentState == WAITING) {
    return ACKNOWLEDGE;
  }
  return currentState;
}

State reduce(State previousState, State newState) {
  if (previousState == WAITING && newState == ACKNOWLEDGE) {
    Serial.println(HANDSHAKE_RESPONSE);
    return READY;
  }

  return newState;
}

State next(State currentState, String action) {
  Command command = adaptCommand(action);
  return reduce(currentState, validateCommand(currentState, command));
}

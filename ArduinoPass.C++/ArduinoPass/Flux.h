#ifndef Flux_h
#define Flux_h

#include "Arduino.h"

typedef enum { WAITING, ACKNOWLEDGE, READY, AUTHENTICATED, BUSY } State;

State next(State, String);

#endif

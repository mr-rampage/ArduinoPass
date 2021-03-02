#ifndef Communication_h
#define Communication_h

#include "Arduino.h"

void initializeCommunication();

void onButtonA(void (* callback)());

void onButtonB(void (* callback)());

void onButtonC(void (* callback)());

void sendPassword(String password);

#endif

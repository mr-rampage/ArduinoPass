#include "Communication.h"
#include <TinyUSB_Mouse_and_Keyboard.h>

#define BUTTON_A 9 // PINB B0000 0010
#define BUTTON_B 6 // PIND B0100 0000
#define BUTTON_C 5 // PIND B0010 0000

#define RE(signal, state) (state=(state<<1)|(signal&1)&3)==1

uint8_t btnState[3];

void initializeCommunication()
{
  Keyboard.begin();
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
}

bool isClicked(int button, int index)
{
  return RE(digitalRead(button), btnState[index]);
}

void onButtonA(void (* callback)())
{
  if (isClicked(BUTTON_A, 0)) {
    callback();
  }
}

void onButtonB(void (* callback)())
{
  if (isClicked(BUTTON_B, 1)) {
    callback();
  }
}

void onButtonC(void (* callback)())
{
  if (isClicked(BUTTON_C, 2)) {
    callback();
  }
}

void sendPassword(String password)
{
  Keyboard.println(password);
}

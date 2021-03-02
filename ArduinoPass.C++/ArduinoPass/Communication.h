#ifndef Communication_h
#define Communication_h

void initializeCommunication();

void sendPassword(String password);

void onButtonA(void (* callback)());

void onButtonB(void (* callback)()); 

void onButtonC(void (* callback)()); 


#endif

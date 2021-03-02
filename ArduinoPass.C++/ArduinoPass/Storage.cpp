#include "Storage.h"
#include <Wire.h>

#define STORAGE_ADDR 9

bool initializeStorage()
{
  Wire.begin();
  return true;
}

bool appendToFile(String filename, String line)
{
  String payload = filename + ":" + line;
  Wire.beginTransmission(STORAGE_ADDR);
  Wire.write(payload.c_str());
  Wire.endTransmission();
  return true;
}

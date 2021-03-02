#include "Storage.h"
#include <SPI.h>
#include <SD.h>

bool initializeStorage()
{
  return SD.begin(4);
}

bool appendToFile(String filename, String line)
{
  File storage = SD.open(filename, FILE_WRITE);

  if (storage) {
    storage.println(line);
    storage.close();
    return true;
  } else {
    return false;
  }
}

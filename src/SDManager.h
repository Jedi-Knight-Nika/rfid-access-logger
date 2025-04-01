
#ifndef SD_MANAGER_H
#define SD_MANAGER_H

#include <Arduino.h>

#include <SD.h>

class SDManager
{
private:
  byte csPin;
  bool sdCardFound;
  String logFileName;

public:
  SDManager(byte chipSelectPin);
  bool begin();
  bool writeLog(String timestamp, String cardID, String cardData);
  bool isSdCardFound();
};

#endif

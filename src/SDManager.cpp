#include "SDManager.h"

SDManager::SDManager(byte chipSelectPin)
{
  csPin = chipSelectPin;
  sdCardFound = false;
  logFileName = "RFID_LOG.CSV";
}

bool SDManager::begin()
{
  sdCardFound = SD.begin(csPin);

  if (sdCardFound)
  {
    if (!SD.exists(logFileName))
    {
      File logFile = SD.open(logFileName, FILE_WRITE);
      if (logFile)
      {
        logFile.println("Timestamp,Card ID,Card Data");
        logFile.close();
      }
      else
      {
        sdCardFound = false;
      }
    }
  }

  return sdCardFound;
}

bool SDManager::writeLog(String timestamp, String cardID, String cardData)
{
  if (!sdCardFound)
    return false;

  File logFile = SD.open(logFileName, FILE_WRITE);
  if (logFile)
  {
    logFile.print(timestamp);
    logFile.print(",");
    logFile.print(cardID);
    logFile.print(",");
    logFile.println(cardData);
    logFile.close();
    return true;
  }

  return false;
}

bool SDManager::isSdCardFound()
{
  return sdCardFound;
}

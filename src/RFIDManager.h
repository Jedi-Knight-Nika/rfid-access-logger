#ifndef RFID_MANAGER_H
#define RFID_MANAGER_H

#include <Arduino.h>

#include <SPI.h>
#include <MFRC522.h>

class RFIDManager
{
private:
  MFRC522 rfid;
  MFRC522::MIFARE_Key key;
  byte blockAddr;

public:
  RFIDManager(byte ssPin, byte rstPin, byte blockAddress);
  void begin();
  bool isCardPresent();
  bool readCardSerial();
  byte *getUID();
  byte getUIDSize();
  String getUIDAsString();
  bool readBlock(byte blockNumber, byte *buffer, byte *bufferSize);
  void stopCrypto();
  String getCardType();
};

#endif

#include "RFIDManager.h"

RFIDManager::RFIDManager(byte ssPin, byte rstPin, byte blockAddress) : rfid(ssPin, rstPin)
{
  blockAddr = blockAddress;

  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
}

void RFIDManager::begin()
{
  rfid.PCD_Init();
}

bool RFIDManager::isCardPresent()
{
  return rfid.PICC_IsNewCardPresent();
}

bool RFIDManager::readCardSerial()
{
  return rfid.PICC_ReadCardSerial();
}

byte *RFIDManager::getUID()
{
  return rfid.uid.uidByte;
}

byte RFIDManager::getUIDSize()
{
  return rfid.uid.size;
}

String RFIDManager::getUIDAsString()
{
  String result = "";
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    if (rfid.uid.uidByte[i] < 0x10)
    {
      result += "0";
    }
    result += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1)
    {
      result += " ";
    }
  }
  result.toUpperCase();
  return result;
}

bool RFIDManager::readBlock(byte blockNumber, byte *buffer, byte *bufferSize)
{
  MFRC522::StatusCode status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumber, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK)
  {
    return false;
  }

  status = rfid.MIFARE_Read(blockNumber, buffer, bufferSize);
  if (status != MFRC522::STATUS_OK)
  {
    return false;
  }

  return true;
}

void RFIDManager::stopCrypto()
{
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

String RFIDManager::getCardType()
{
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  return String(rfid.PICC_GetTypeName(piccType));
}

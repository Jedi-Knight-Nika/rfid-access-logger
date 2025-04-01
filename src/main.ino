#include <SPI.h>
#include <Wire.h>
#include "RFIDManager.h"
#include "DisplayManager.h"
#include "TimeManager.h"
#include "SDManager.h"
#include "NotificationManager.h"

#define RFID_SS_PIN 10
#define RFID_RST_PIN 9
#define BUZZER_PIN 7
#define LED_PIN 6
#define SD_CS_PIN 4

#define BLOCK_ADDR 4

RFIDManager rfidManager(RFID_SS_PIN, RFID_RST_PIN, BLOCK_ADDR);
DisplayManager displayManager(0x27, 16, 2);
TimeManager timeManager;
SDManager sdManager(SD_CS_PIN);
NotificationManager notificationManager(BUZZER_PIN, LED_PIN);

byte cardDataBuffer[18];
byte bufferSize = sizeof(cardDataBuffer);

void setup()
{
  Serial.begin(9600);

  SPI.begin();

  rfidManager.begin();
  displayManager.begin();
  notificationManager.begin();

  if (!timeManager.begin())
  {
    Serial.println("Couldn't find RTC");
    displayManager.displayError("No RTC found");
    delay(2000);
  }
  else
  {

    Serial.print("Current time: ");
    Serial.println(timeManager.getTimestamp());
  }

  if (!sdManager.begin())
  {
    Serial.println("SD card initialization failed!");
    displayManager.displayError("No SD card");
    delay(2000);
  }
  else
  {
    Serial.println("SD card initialized");
  }

  displayManager.displayWelcomeScreen();
  Serial.println("RFID Card Reader System Ready");
  Serial.println("Scan a card to begin");
}

void loop()
{
  if (!rfidManager.isCardPresent())
  {
    return;
  }

  if (!rfidManager.readCardSerial())
  {
    return;
  }

  notificationManager.successNotification();

  String cardUID = rfidManager.getUIDAsString();
  Serial.print("Card UID: ");
  Serial.println(cardUID);

  displayManager.displayCardID(cardUID);
  delay(1500);

  bool readSuccess = rfidManager.readBlock(BLOCK_ADDR, cardDataBuffer, &bufferSize);

  String timestamp = timeManager.getTimestamp();

  if (readSuccess)
  {
    displayManager.displayCardData(cardDataBuffer, 16);
    delay(2000);

    displayManager.displayDataAsHex(cardDataBuffer, 16);

    String cardDataStr = "";
    for (byte i = 0; i < 16; i++)
    {
      if (cardDataBuffer[i] < 0x10)
      {
        cardDataStr += "0";
      }
      cardDataStr += String(cardDataBuffer[i], HEX);
      if (i < 15)
      {
        cardDataStr += " ";
      }
    }

    if (sdManager.isSdCardFound())
    {
      if (sdManager.writeLog(timestamp, cardUID, cardDataStr))
      {
        Serial.println("Data logged to SD card");
      }
      else
      {
        Serial.println("Failed to log data");
        displayManager.displayError("Log failed");
        notificationManager.errorNotification();
        delay(1000);
      }
    }

    Serial.print("Time: ");
    Serial.println(timestamp);
    Serial.print("Card Data: ");
    Serial.println(cardDataStr);
  }
  else
  {
    Serial.println("Failed to read card data");
    displayManager.displayError("Read failed");
    notificationManager.errorNotification();
    delay(1000);
  }

  rfidManager.stopCrypto();

  delay(1500);
  displayManager.displayWelcomeScreen();
}
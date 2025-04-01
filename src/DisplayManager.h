#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

class DisplayManager
{
private:
  LiquidCrystal_I2C lcd;

public:
  DisplayManager(uint8_t lcdAddr, uint8_t cols, uint8_t rows);
  void begin();
  void clear();
  void displayWelcomeScreen();
  void displayCardID(String cardID);
  void displayCardData(byte *buffer, byte bufferSize);
  void displayDataAsHex(byte *buffer, byte bufferSize);
  void displayMessage(String line1, String line2);
  void displayError(String errorMsg);
};

#endif

#include "DisplayManager.h"

DisplayManager::DisplayManager(uint8_t lcdAddr, uint8_t cols, uint8_t rows) : lcd(lcdAddr, cols, rows)
{
}

void DisplayManager::begin()
{
  lcd.init();
  lcd.backlight();
}

void DisplayManager::clear()
{
  lcd.clear();
}

void DisplayManager::displayWelcomeScreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID Card Reader");
  lcd.setCursor(0, 1);
  lcd.print("Scan a card...");
}

void DisplayManager::displayCardID(String cardID)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card ID:");
  lcd.setCursor(0, 1);

  if (cardID.length() > 16)
  {
    cardID = cardID.substring(0, 16);
  }

  lcd.print(cardID);
}

void DisplayManager::displayCardData(byte *buffer, byte bufferSize)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card Data:");
  lcd.setCursor(0, 1);

  for (byte i = 0; i < 16 && i < bufferSize; i++)
  {
    if (buffer[i] >= 32 && buffer[i] <= 126)
    {
      lcd.print((char)buffer[i]);
    }
    else
    {
      lcd.print('.');
    }
  }
}

void DisplayManager::displayDataAsHex(byte *buffer, byte bufferSize)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Data (HEX):");
  lcd.setCursor(0, 1);

  for (byte i = 0; i < 8 && i < bufferSize; i++)
  {
    if (buffer[i] < 0x10)
    {
      lcd.print('0');
    }
    char hexStr[3];
    sprintf(hexStr, "%02X", buffer[i]);
    lcd.print(hexStr);
    if (i < 7)
    {
      lcd.print(' ');
    }
  }
}

void DisplayManager::displayMessage(String line1, String line2)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  if (line2.length() > 0)
  {
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}

void DisplayManager::displayError(String errorMsg)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error:");
  lcd.setCursor(0, 1);
  lcd.print(errorMsg);
}

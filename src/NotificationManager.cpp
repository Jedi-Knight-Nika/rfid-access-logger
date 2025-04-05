#include "NotificationManager.h"
#include <Arduino.h>

int buzzerPin;
int ledPin;

NotificationManager::NotificationManager(byte buzzerPinNumber, byte ledPinNumber)
{
  buzzerPin = buzzerPinNumber;
  ledPin = ledPinNumber;
}

void NotificationManager::begin()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
}

void NotificationManager::successNotification()
{
  digitalWrite(ledPin, HIGH);

  tone(buzzerPin, 1000, 200);
  delay(200);

  delay(800);
  digitalWrite(ledPin, LOW);
}

void NotificationManager::errorNotification()
{
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 300, 200);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}

void NotificationManager::waitingNotification()
{
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}

#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <Arduino.h>

class NotificationManager {
private:
  byte buzzerPin;
  byte ledPin;

public:
  NotificationManager(byte buzzerPinNumber, byte ledPinNumber);
  void begin();
  void successNotification();
  void errorNotification();
  void waitingNotification();
};

#endif

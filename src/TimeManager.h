#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <RTClib.h>

class TimeManager
{
private:
  RTC_DS3231 rtc;
  bool rtcFound;

public:
  TimeManager();
  bool begin();
  void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
  String getFormattedDate();
  String getFormattedTime();
  String getTimestamp();
  bool isRTCFound();
  unsigned long getEpochTime();
};

#endif

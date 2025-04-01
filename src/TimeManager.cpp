#include "TimeManager.h"

TimeManager::TimeManager()
{
  rtcFound = false;
}

bool TimeManager::begin()
{
  rtcFound = rtc.begin();
  return rtcFound;
}

void TimeManager::setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
  if (rtcFound)
  {
    rtc.adjust(DateTime(year, month, day, hour, minute, second));
  }
}

String TimeManager::getFormattedDate()
{
  if (!rtcFound)
    return "No RTC found";

  DateTime now = rtc.now();
  char dateStr[11];
  sprintf(dateStr, "%04d-%02d-%02d", now.year(), now.month(), now.day());
  return String(dateStr);
}

String TimeManager::getFormattedTime()
{
  if (!rtcFound)
    return "No RTC found";

  DateTime now = rtc.now();
  char timeStr[9];
  sprintf(timeStr, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  return String(timeStr);
}

String TimeManager::getTimestamp()
{
  if (!rtcFound)
    return "No RTC found";

  DateTime now = rtc.now();
  char timestamp[20];
  sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());
  return String(timestamp);
}

bool TimeManager::isRTCFound()
{
  return rtcFound;
}

unsigned long TimeManager::getEpochTime()
{
  if (!rtcFound)
    return 0;

  DateTime now = rtc.now();
  return now.unixtime();
}

#include "plugins/ClockPlugin.h"

void ClockPlugin::setup()
{
  // loading screen
  Screen.setPixel(4, 7, 1);
  Screen.setPixel(5, 7, 1);
  Screen.setPixel(7, 7, 1);
  Screen.setPixel(8, 7, 1);
  Screen.setPixel(10, 7, 1);
  Screen.setPixel(11, 7, 1);

  previousMinutes = -1;
  previousHour = -1;
  previousSeconds = -1;
}

void ClockPlugin::loop()
{
  if (getLocalTime(&timeinfo))
  {
    if (previousHour != timeinfo.tm_hour || previousMinutes != timeinfo.tm_min || previousSeconds != timeinfo.tm_sec)
    {
      Screen.clear();
      Screen.drawNumbers(3, 2, {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10});
      Screen.drawNumbers(3, 8, {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10});
    }

    // Seconds pip
    int second = timeinfo.tm_sec;
    int x, y;

    if (second <= 7)
    {
      x = 8 + second;
      y = 0;
    }
    else if (second <= 22)
    {
      x = 15;
      y = (second - 7);
    }
    else if (second <= 37)
    {
      x = 15 - (second - 22);
      y = 15;
    }
    else if (second <= 52)
    {
      x = 0;
      y = 15 - (second - 37);
    }
    else
    {
      x = second - 52;
      y = 0;
    }

    Screen.setPixel(x, y, 1, 255);

    previousMinutes = timeinfo.tm_min;
    previousHour = timeinfo.tm_hour;
    previousSeconds = timeinfo.tm_sec;
  }
}

const char *ClockPlugin::getName() const
{
  return "Clock";
}

#pragma once

#include <cstdint>
#include <chrono>

namespace Pinetime {
  namespace System {
    class SystemTask;
  }
  namespace Controllers {
    class DateTime {
    public:
      enum class Days : uint8_t { Unknown, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
      enum class Months : uint8_t {
        Unknown,
        January,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
      };

      DateTime(System::SystemTask& systemTask);

      void SetAlarm(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute);

      void UnsetAlarm(){
	      alarm_running = false;
      }

      bool AlarmRunning(){
	      return alarm_running;
      }

      void SetTime(uint16_t year,
                   uint8_t month,
                   uint8_t day,
                   uint8_t dayOfWeek,
                   uint8_t hour,
                   uint8_t minute,
                   uint8_t second,
                   uint32_t systickCounter);
      void UpdateTime(uint32_t systickCounter);
      uint16_t Year() const {
        return year;
      }
      Months Month() const {
        return month;
      }
      uint8_t Day() const {
        return day;
      }
      Days DayOfWeek() const {
        return dayOfWeek;
      }
      uint8_t Hours() const {
        return hour;
      }
      uint8_t Minutes() const {
        return minute;
      }
      uint8_t Seconds() const {
        return second;
      }
      uint8_t AlarmHour() const{
	      return alarm_hour;
      }
      uint8_t AlarmMinute() const{
	      return alarm_minute;
      }

      const char* MonthShortToString();
      const char* MonthShortToStringLow();
      const char* MonthsToStringLow();
      const char* DayOfWeekToString();
      const char* DayOfWeekShortToString();
      const char* DayOfWeekToStringLow();
      const char* DayOfWeekShortToStringLow();

      std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> CurrentDateTime() const {
        return currentDateTime;
      }
      std::chrono::seconds Uptime() const {
        return uptime;
      }

    private:
      System::SystemTask& systemTask;
      uint16_t year = 0;
      Months month = Months::Unknown;
      uint8_t day = 0;
      Days dayOfWeek = Days::Unknown;
      uint8_t hour = 0;
      uint8_t minute = 0;
      uint8_t second = 0;
      uint16_t alarm_year = 0;
      uint8_t alarm_month = 0;
      uint8_t alarm_day = 0;
      uint8_t alarm_hour = 0;
      uint8_t alarm_minute = 0;
      bool alarm_running = false;

      uint32_t previousSystickCounter = 0;
      std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> currentDateTime;
      std::chrono::seconds uptime {0};

      bool isMidnightAlreadyNotified = false;

      static char const* DaysString[];
      static char const* DaysStringShort[];
      static char const* DaysStringLow[];
      static char const* DaysStringShortLow[];
      static char const* MonthsString[];
      static char const* MonthsStringLow[];
      static char const* MonthsLow[];
    };
  }
}

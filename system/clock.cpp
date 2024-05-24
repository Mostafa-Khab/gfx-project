#include <string>
#include <ctime>
#include "clock.hpp"

namespace gfx
{

  clock::clock()
  {
    m_start = std::chrono::high_resolution_clock::now();
  }

  float clock::elapsed()
  {
    using namespace std::chrono;

    auto end = high_resolution_clock::now();
    duration<float> d = end - m_start;

    return d.count();

  }

  float clock::restart()
  {
    using namespace std::chrono;

    auto end = high_resolution_clock::now();
    duration<float> d = end - m_start;

    m_start = end;

    return d.count();

  }

  //clock_T can be high_resolution_clock or system_clock or steady_clock only!
  std::chrono::system_clock::time_point datetime(int year, int month, int day)
  {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);

    timeinfo = localtime(&rawtime);
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon  = month - 1;
    timeinfo->tm_mday = day;

    rawtime = mktime(timeinfo);
    return std::chrono::system_clock::from_time_t(rawtime);
  }

  std::chrono::system_clock::time_point datetime(int year, int mon, int day, int hour, int minute)
  {
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);

    timeinfo = localtime(&rawtime);
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon  = mon - 1;
    timeinfo->tm_mday = day;
    timeinfo->tm_hour = hour - 1;
    timeinfo->tm_min  = minute;

    rawtime = mktime(timeinfo);
    return std::chrono::system_clock::from_time_t(rawtime);
  }

  std::string strtime(const std::chrono::system_clock::time_point& tp)
  {
    time_t t = std::chrono::system_clock::to_time_t(tp);
    return ctime(&t);
  }

}

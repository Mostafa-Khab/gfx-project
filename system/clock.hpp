/*********************************
 * author     : mostafa khaled
 * date       : Tue Mar  5 09:15:55 PM EET 2024
 * desc       : 
 ********************************/
#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class Clock
{
  public:
    Clock();
   ~Clock() = default;

   float elapsed();
   float restart();

  private:
    std::chrono::high_resolution_clock::time_point m_start;
};

  std::chrono::system_clock::time_point datetime(int year, int month, int day, int hour, int minute);
  std::chrono::system_clock::time_point datetime(int year, int month, int day);
  std::string strtime(const std::chrono::system_clock::time_point& tp);

#endif /* !CLOCK_HPP */

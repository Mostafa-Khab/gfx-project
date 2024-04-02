/*********************************
 * author     : mostafa khaled
 * date       : Wed Mar  6 11:24:52 AM EET 2024
 * desc       : switching to raw input terminal mode
 ********************************/
#ifndef RAW_INPUT_HPP
#define RAW_INPUT_HPP

#include <iostream>
#include <termios.h>

class raw_input
{
  public:
    raw_input(int echo = 0)
    {
      tcgetattr(0, &m_old);
      cfmakeraw(&m_new);
      tcsetattr(0, TCSANOW, &m_new);
    }

   ~raw_input()
    {
      tcsetattr(0, TCSANOW, &m_old);
    }

    void restore()
    {
      tcsetattr(0, TCSANOW, &m_old);
    }

    void activate()
    {
      tcsetattr(0, TCSANOW, &m_new);
    }

  private:
   struct termios m_old, m_new; 
};

void clear(std::ostream& strm)
{
  strm << "\033[2J\033[1;1H";
}

#endif /* !RAW_INPUT_HPP */

#include <GLFW/glfw3.h>
#include <iostream>
#include <string_view>


#include "debug.hpp"

namespace test
{
  void print(std::string_view message)
  {
    std::cout << message << '\n';
  }

  void dprint(std::string_view message)
  {
#if defined(DEBUG) | defined(_DEBUG)
    std::cout << message << '\n';
#endif
  }



#if defined(__MINGW32__) | defined(__MINGW64__)
  char pause()
  {
    return std::cin.get();
  }
#else
#include <raw_input.h>

  char pause()
  {
    raw_input ri;
    return std::cin.get();
  }
#endif
}

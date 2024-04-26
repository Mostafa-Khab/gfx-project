#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


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

  void assert(bool expr, std::string_view msg, int code)
  {
    if(!expr)
    {
      std::cerr << msg << '\n';
      std::exit(code);
    }
  }

  void dassert(bool expr, std::string_view msg, int code)
  {
#if defined(DEBUG) | defined(_DEBUG)
    if(!expr)
    {
      std::cerr << msg << '\n';
      std::exit(code);
    }
#endif
  }

  void glfw_assert(bool expr, std::string_view msg, int code)
  {
    if(!expr)
    {
      std::cerr << msg << '\n';
      glfwTerminate();
      std::exit(code);
    }
  }

  void dglfw_assert(bool expr, std::string_view msg, int code)
  {
#if defined(DEBUG) | defined(_DEBUG)
    if(!expr)
    {
      std::cerr << msg << '\n';
      glfwTerminate();
      std::exit(code);
    }
#endif
  }

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

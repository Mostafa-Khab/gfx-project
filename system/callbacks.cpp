#include <GLFW/glfw3.h>

#include <iostream>

#include "callbacks.hpp"

namespace gfx
{

  namespace callback
  {

    void error(int error, const char* desc)
    {
      std::cerr << "Error-> " << desc << '\n';
    }

    void key(GLFWwindow* window, int key, int scancode,
            int action, int mods)
    {
      if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }
    }

  }

}


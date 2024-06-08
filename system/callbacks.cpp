#include <GLFW/glfw3.h>

#include <iostream>

#include "callbacks.hpp"

namespace gfx
{

  double mouse::x = 0.f;
  double mouse::y = 0.f;
  int mouse::button = 0;
  bool mouse::pressed = false;

  void mouse::update(GLFWwindow* window)
  {
      glfwGetCursorPos(window, &mouse::x, &mouse::y);
      int width = 0, height = 0;
      glfwGetWindowSize(window, &width, &height);

      mouse::x = (mouse::x / width ) * 2.0;
      mouse::y = (mouse::y / height) * 2.0;
      
      mouse::x -= 1.0;
      mouse::y -= 1.0; mouse::y *= -1.0;
  }

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

    void button(GLFWwindow* window, int button , int action , int mods)
    {
      if(action == GLFW_PRESS)
        mouse::pressed = true;
      else if(action == GLFW_RELEASE)
        mouse::pressed = false;

      mouse::button = button;

      
    }

  }

}


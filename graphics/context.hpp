/************************* 
 *  author : mostafa khaled 
 *  date   : Tue Feb  6 07:53:55 PM EET 2024
 *  why    : simplify OpenGL
*************************/ 

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <GLFW/glfw3.h>
#include <string>

#include "../system/color.hpp"

namespace gfx
{

  class context
  {
    public:
     struct version
     {
       int major;
       int minor;
     };

    public:
      context();
     ~context();

     void setVersion   (version v);
     version getVersion();

     void setWindowData(int w, int h, std::string name, bool fullscreen = false);

     bool init();

    // void createWindow(int width, int height, std::string name);
     void getWindow(GLFWwindow*& window);

     void clear(float r = 0, float g = 0, float b = 0, float a = 1, int targets = GL_COLOR_BUFFER_BIT);
     void clear(rgba color = rgba(0,0,0,1), int targets = GL_COLOR_BUFFER_BIT);
     void display();

     bool should_close();
     void terminate();

    private:
     GLFWwindow* m_window;
     version     m_version;

     int         m_window_size_x;
     int         m_window_size_y;
     std::string m_window_name;

     bool        m_terminated;
     bool        m_fullscreen;

  };

}
#endif

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

#include "context.hpp"
#include "../system/debug.hpp"

namespace gfx
{

  context::context() : m_terminated(false)
  {

  }

  context::~context()
  {
      terminate();
  }

  void context::setVersion(context::version v)
  {
    m_version.major = v.major;
    m_version.minor = v.minor;
  }

  void context::setWindowData(int w, int h, std::string name)
  {
    m_window_size_x = w;
    m_window_size_y = h;
    m_window_name   = name;
  }

  context::version context::getVersion()
  {
    return { m_version.major, m_version.minor};
  }

  bool context::init()
  {
    if(!glfwInit())
    {
      return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_version.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_version.minor);

    m_window = glfwCreateWindow(m_window_size_x, m_window_size_y,
                                m_window_name.c_str(),
                                NULL, NULL);
    if(!m_window)
    {
      Log::debug("failed to create window in context::init()");
      return false;
    }

    glfwMakeContextCurrent(m_window);
    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, m_window_size_x, m_window_size_y);

    return true;

  }

  void context::getWindow(GLFWwindow*& window)
  {
    window = m_window;
  }

  void context::clear(float r, float g, float b, float a, int targets)
  {
    glClearColor(r, g, b, a);
    glClear(targets);
  }

  void context::clear(rgba c, int targets)
  {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(targets);
  }

  void context::display()
  {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
  }

  bool context::should_close()
  {
    return glfwWindowShouldClose(m_window);
  }

  void context::terminate()
  {
    if(!m_terminated)
    {
      m_terminated = true;
      glfwTerminate();
      Log::debug("shutdown opengl context");
    }
  }

}

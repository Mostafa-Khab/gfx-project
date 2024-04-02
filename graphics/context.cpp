#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

#include "context.hpp"
#include "../system/debug.hpp"

Context::Context() : m_terminated(false)
{

}

Context::~Context()
{
    terminate();
}

void Context::setVersion(Context::version v)
{
  m_version.major = v.major;
  m_version.minor = v.minor;
}

void Context::setWindowData(int w, int h, std::string name)
{
  m_window_size_x = w;
  m_window_size_y = h;
  m_window_name   = name;
}

Context::version Context::getVersion()
{
  return { m_version.major, m_version.minor};
}

bool Context::init()
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
    return false;
  }

  glfwMakeContextCurrent(m_window);
  gladLoadGL(glfwGetProcAddress);
  glViewport(0, 0, m_window_size_x, m_window_size_y);

  return true;

}

void Context::getWindow(GLFWwindow*& window)
{
  window = m_window;
}

void Context::clear(float r, float g, float b, float a, int targets)
{
  glClearColor(r, g, b, a);
  glClear(targets);
}

void Context::clear(RGBA c, int targets)
{
  glClearColor(c.r, c.g, c.b, c.a);
  glClear(targets);
}

void Context::display()
{
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

bool Context::should_close()
{
  return glfwWindowShouldClose(m_window);
}

void Context::terminate()
{
  if(!m_terminated)
  {
    m_terminated = true;
    glfwTerminate();
  }
}

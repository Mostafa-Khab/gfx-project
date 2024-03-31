#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "view.hpp"

View::View(int width , int height): m_width(width), m_height(height), m_ratio((width / (float)height)), m_prespective(false)
{
  mat4x4_identity(_m);
}



void View::set_mvp(int& mvp_location)
{
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE ,(const float *)_mvp);
}

void View::update(GLFWwindow* window)
{
  glfwGetFramebufferSize(window, &m_width, &m_height);
  m_ratio = m_width / (float)m_height;
  glViewport(0, 0, m_width, m_height);

}

void View::multiply()
{
  if(m_prespective)
    mat4x4_mul(_p, _p, _v);

  mat4x4_mul(_mvp, _p, _m)  ;
}

void View::rotate_X(float angle)
{
  mat4x4_rotate_X(_m, _m, angle);
}

void View::rotate_Y(float angle)
{
  mat4x4_rotate_Y(_m, _m, angle);
}

void View::rotate_Z(float angle)
{
  mat4x4_rotate_Z(_m, _m, angle);
}

void View::ortho(float n, float f)
{
  mat4x4_ortho(_p, -m_ratio, m_ratio, -1.f, 1.f, n, f);
  m_prespective = false;
}

void View::perspective(float fov, float n, float f)
{
  mat4x4_perspective(_p, fov, m_ratio, n, f);
  m_prespective = true;
}

void View::view(vec3 eye, vec3 centre, vec3 up)
{
  mat4x4_look_at(_v, eye, centre, up);
}

mat4x4& View::mvp()
{
  return _mvp;
}

mat4x4& View::m()
{
  return _m;
}

mat4x4& View::p()
{
  return _p;
}

mat4x4& View::v()
{
  return _v;
}

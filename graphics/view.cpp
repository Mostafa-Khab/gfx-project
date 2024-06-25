#include <glad/gl.h>
#define GLFW_INCLUDE_NONE //can this cause an error
#include <GLFW/glfw3.h>

#include "view.hpp"

namespace gfx
{

  view::view(int width , int height): m_width(width), m_height(height), m_ratio((width / (float)height)), m_prespective(false), m_centre(0, 0, 0)
  {
    mat4x4_identity(_m);
    instance() = this;
  }



  void view::set_mvp(int& mvp_location)
  {
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE ,(const float *)_mvp);
  }

  void view::update(GLFWwindow* window)
  {
    glfwGetFramebufferSize(window, &m_width, &m_height);
    m_ratio = m_width / (float)m_height;
    glViewport(0, 0, m_width, m_height);

  }

  void view::multiply()
  {
    if(m_prespective)
      mat4x4_mul(_p, _p, _v);

    mat4x4_mul(_mvp, _p, _m)  ;
  }

  void view::rotate_X(float angle)
  {
    mat4x4_rotate_X(_m, _m, angle);
  }

  void view::rotate_Y(float angle)
  {
    mat4x4_rotate_Y(_m, _m, angle);
  }

  void view::rotate_Z(float angle)
  {
    mat4x4_rotate_Z(_m, _m, angle);
  }

  void view::ortho(float min, float max)
  {
    mat4x4_ortho(_p,
                 m_ratio * min + m_centre.x,
                 m_ratio * max + m_centre.x,
                 m_ratio * min + m_centre.y,
                 m_ratio * max + m_centre.y,
                 -1 + m_centre.z,
                 1 + m_centre.z);
    m_prespective = false;
  }

  void view::perspective(float fov, float n, float f)
  {
    mat4x4_perspective(_p, fov, m_ratio, n, f);
    m_prespective = true;
  }

  void view::data(vector3f eye, vector3f centre, vector3f up)
  {
    //WARNING: this may cause the app to crash. but I will try it anyway.
    mat4x4_look_at(
        _v,
        reinterpret_cast<float*>(&eye),
        reinterpret_cast<float*>(&centre),
        reinterpret_cast<float*>(&up)
    );
  }

  mat4x4& view::mvp()
  {
    return _mvp;
  }

  mat4x4& view::m()
  {
    return _m;
  }

  mat4x4& view::p()
  {
    return _p;
  }

  mat4x4& view::v()
  {
    return _v;
  }

  float view::aspect()
  {
    return m_ratio;
  }

  void view::set_centre(float x, float y, float z)
  {
    m_centre.x = x;
    m_centre.y = y;
    m_centre.z = z;
  }

  void view::move_centre(float x, float y, float z)
  {
    m_centre.x += x;
    m_centre.y += y;
    m_centre.z += z;
  }

  const vector3f& view::get_centre()
  {
    return m_centre;
  }

  void view::set_instance_current()
  {
    instance() = this;
  }

  void view::callback(GLFWwindow* window, int w, int h)
  {
    instance()->m_width  = w; 
    instance()->m_height = h; 

    instance()->m_ratio = instance()->m_width / (float)instance()->m_height;
    glViewport(0, 0, instance()->m_width, instance()->m_height);
  }
}

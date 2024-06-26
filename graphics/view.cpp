#include <glad/gl.h>
#define GLFW_INCLUDE_NONE //can this cause an error
#include <GLFW/glfw3.h>

#include "vectors.hpp"

#include "view.hpp"

namespace gfx
{

  view::view(int width , int height): m_width(width), m_height(height), m_ratio((width / (float)height)), m_prespective(false)
  {
    mat4x4_identity(_m);
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

  void view::ortho(float n, float f)
  {
    mat4x4_ortho(_p, -m_ratio, m_ratio, -1.f, 1.f, n, f);
    m_prespective = false;
  }

  void view::perspective(float fov, float n, float f)
  {
    mat4x4_perspective(_p, fov, m_ratio, n, f);
    m_prespective = true;
  }

  void view::data(vector3f eye, vector3f centre, vector3f up)
  {
    vec3 eye_    { eye.x , eye.y, eye.z };
    vec3 centre_ { centre.x , centre.y, centre.z };
    vec3 up_     { up.x , up.y, up.z};
    mat4x4_look_at(_v, eye_, centre_, up_);
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

}

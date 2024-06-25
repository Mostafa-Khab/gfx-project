/*********************************
 * author     : mostafa khaled
 * date       : Mon Mar 11 11:19:59 AM EET 2024
 * desc       : 
 ********************************/
#ifndef VIEW_HPP
#define VIEW_HPP

#include "linmath.h"

class GLFWwindow;

namespace gfx
{

  template<typename T> struct vector3;

  class view 
  {
    public:
      view(int width = 800, int height = 600);
     ~view() = default;

     void set_mvp(int& mvp_location);
     void update(GLFWwindow* window);
     void multiply();

     void rotate_X(float angle);
     void rotate_Y(float angle);
     void rotate_Z(float angle);

     void ortho(float min = -1, float max = 1);
     void perspective(float fov = 3.1415 / 4, float n = 0, float f = 10);
     void data(vector3<float> eye, vector3<float> center, vector3<float> up);

     mat4x4& mvp();
     mat4x4& m();
     mat4x4& p();
     mat4x4& v();


    private:
      mat4x4    _mvp, _m, _p, _v;
      int       m_width;
      int       m_height;
      float     m_ratio;
      bool      m_prespective;
  };

}
#endif /* !VIEW_HPP */

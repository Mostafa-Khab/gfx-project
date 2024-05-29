/*********************************
 * author     : mostafa khaled
 * date       : Fri May 24 02:10:27 PM EEST 2024
 * desc       : 
 ********************************/
#ifndef INTERPOLATORS_HPP
#define INTERPOLATORS_HPP

#include "vectors.hpp"

namespace gfx
{

  float lerp(float a , float b , float t);

  vector2f lerp(const vector2f& start, const vector2f& finish, float t);
  vector2f lerp(vector2f&& start, vector2f&& finish, float t);

  vector3f lerp(const vector3f& start, const vector3f& finish, float t);
  vector3f lerp(vector3f&& start, vector3f&& finish, float t);

  float clamp(float v, float min, float max);

  //ease functions
  float smoothstep(float t);

  namespace cubic 
  {
    float ease_in(float x);
    float ease_out(float x);
    float ease_inout(float x);
  }
}

#endif /* !INTERPOLATORS_HPP */

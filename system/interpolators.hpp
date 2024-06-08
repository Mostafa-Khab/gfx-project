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
  struct rgb;
  struct rgba;

  float lerp(float a , float b , float t);

  vector2f lerp(const vector2f& start, const vector2f& finish, float t);
  vector2f lerp(vector2f&& start, vector2f&& finish, float t);

  vector3f lerp(const vector3f& start, const vector3f& finish, float t);
  vector3f lerp(vector3f&& start, vector3f&& finish, float t);

  rgb lerp(const rgb& start, const rgb& end, float t);
  rgb lerp(rgb&& start, rgb&& end, float t);

  rgba lerp(const rgba& start, const rgba& end, float t);
  rgba lerp(rgba&& start, rgba&& end, float t);

  float clamp(float v, float min, float max);

  //ease functions
  float smoothstep(float t);

  namespace quad
  {
    float ease_in(float x);
    float ease_out(float x);
    float ease_inout(float x);
    float pump_out(float x);
  }

  namespace cubic 
  {
    float ease_in(float x);
    float ease_out(float x);
    float ease_inout(float x);
    float pump_out(float x);
    float pump_inout(float x);
  }

  namespace quart
  {
    float ease_in(float x);
    float ease_out(float x);
    float pump_out(float x);
    float ease_inout(float x);
  }

  namespace bounce
  {
    float ease_out(float x);
    float ease_in(float x);
    float ease_inout(float x);
  }
}

#endif /* !INTERPOLATORS_HPP */

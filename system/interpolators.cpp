#include "color.hpp"
#include "interpolators.hpp"

namespace gfx
{
  float lerp(float a, float b, float t)
  {
    return a + (b - a) * t;
  }

  vector2f lerp(const vector2f& start, const vector2f& finish, float t)
  {
    return vector2f(lerp(start.x , finish.x, t), lerp(start.y, finish.y, t));
  }
  vector2f lerp(vector2f&& start, vector2f&& finish, float t)
  {
    return vector2f(lerp(start.x , finish.x, t), lerp(start.y, finish.y, t));
  }

  vector3f lerp(const vector3f& start, const vector3f& finish,float t)
  {
    return vector3(lerp(start.x, finish.x, t), lerp(start.y, finish.y, t), lerp(start.z, finish.z, t));
  }

  vector3f lerp(vector3f&& start, vector3f&& finish, float t)
  {
    return vector3(lerp(start.x, finish.x, t), lerp(start.y, finish.y, t), lerp(start.z, finish.z, t));
  }

  rgb lerp(const rgb& c1, const rgb& c2, float t)
  {
    return rgb(lerp(c1.r, c2.r, t), lerp(c1.g, c2.g, t), lerp(c1.b, c2.b, t));
  }

  rgb lerp(rgb&& c1, rgb&& c2, float t)
  {
    return rgb(lerp(c1.r, c2.r, t), lerp(c1.g, c2.g, t), lerp(c1.b, c2.b, t));
  }

  rgba lerp(const rgba& c1, const rgba& c2, float t)
  {
    return rgba(lerp(c1.r, c2.r, t), lerp(c1.g, c2.g, t), lerp(c1.b, c2.b, t), lerp(c1.a, c2.a, t));
  }

  rgba lerp(rgba&& c1, rgba&& c2, float t)
  {
    return rgba(lerp(c1.r, c2.r, t), lerp(c1.g, c2.g, t), lerp(c1.b, c2.b, t), lerp(c1.a, c2.a, t));
  }

  float clamp(float v, float min, float max)
  {
    const float t = (v < min)? min : v;
    return (t > max)? max : t;
  }

  float smoothstep(float t)
  {
    return t * t * (3 - 2 * t);
  }

  namespace cubic
  {
    float ease_in(float x)
    {
      return x * x * x;
    }

    float ease_out(float x)
    {
      return 1.f - (1.f - x) * (1.f - x) * (1.f - x);
    }

    float ease_inout(float x)
    {
      if(x < 0.5)
        return 4.f * x * x * x;

      return 1.f - (-2.f * x + 2.f) * (-2.f * x + 2.f) * (-2.f * x + 2.f) / 2.f;
    }
  }
}

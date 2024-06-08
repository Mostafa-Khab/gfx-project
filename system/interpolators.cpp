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

  namespace quad
  {
    float ease_in(float x)
    {
      return x * x;
    }

    float ease_out(float x)
    {
      return 1.f - (1.f - x) * (1.f - x);
    }

    float ease_inout(float x)
    {
      return x < 0.5 ? 2 * x * x : 1 - (-2 * x + 2) * (-2 * x + 2) / 2;
    }

    float pump_out(float x)
    {
      if (x <= 0.8f)
        return 1.5625f * x * x;

      return 1.125f - 12.5f * (0.9 - x) * (0.9 - x);
    }
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
      return (x < 0.5) ?  4.f * x * x * x : 1.f - (-2.f * x + 2.f) * (-2.f * x + 2.f) * (-2.f * x + 2.f) / 2.f;
    }

    float pump_out(float x)
    {
      if (x <= 0.8f)
        return 1.953f * x * x * x;

      return 1.1875 - 18.75 * (0.9 - x) * (0.9 - x);
    }

    float pump_inout(float x)
    {
      if(x <= 0.2f)
        return -0.25f + 25.f * (0.1 - x) * (0.1 - x);
      else if(x >= 0.8f)
        return 1.25f - 25.f * (0.9 - x) * (0.9 - x);

      return 0.5f - 18.519f * (0.5f - x) * (0.5f - x) * (0.5f - x);
    }
  }

  namespace quart
  {
    float ease_in(float x)
    {
      return x * x * x * x;
    }

    float ease_out(float x)
    {
      return 1.f - (1.f - x) * (1.f - x) * (1.f - x) * (1.f - x);
    }

    float ease_inout(float x)
    {
      return x < 0.5 ? 8 * x * x * x * x : 1 - (-2 * x + 2) * (-2 * x + 2) * (-2 * x + 2) * (-2 * x + 2) / 2;
    }

    float pump_out(float x)
    {
      if (x <= 0.8f)
        return 2.4414f * x * x * x * x;

      return 1.25f - 25.f * (0.9 - x) * (0.9 - x);
    }
  }


  namespace bounce
  {
    const float n1 = 7.5625;
    const float d1 = 2.75;

    float ease_out(float t)
    {

      if(t < 1.f / d1)
      {
        return n1 * t * t;
      } else if(t < 2.f / d1)
      {
        return n1 * (t -= 1.5f / d1) * t +  0.75f;
      } else if(t < 2.5f / d1)
      {
        return n1 * (t -= 2.25f / d1) * t + 0.9375f;
      } 

      return n1 * (t -= 2.625f / d1) * t + 0.984375f;
    }

    float ease_in(float x)
    {
      return 1 - ease_out(1 - x);
    }

    float ease_inout(float x)
    {
      return (x < 0.5)? (1 - ease_out(1 - 2 * x)) / 2
                      : (1 + ease_out(2 * x - 1)) / 2;
    }
  }
}

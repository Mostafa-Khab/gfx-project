#include "interpolators.hpp"

namespace gfx
{
  float lerp(float a, float b, float t)
  {
    return a + (b - a) * t;
  }

  float clamp(float v, float min, float max)
  {
    const float t = (v < min)? min : v;
    return (t > max)? max : t;
  }
}

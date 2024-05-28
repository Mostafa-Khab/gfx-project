#include "box.hpp"

namespace gfx
{
  bool box::intersects(const box& b)
  {
    return (x - (0.5 * width) <= b.x + (0.5 * b.width) && x + (0.5 * width) >= b.x - (0.5 * b.width)) &&
           (y - (0.5 * width) <= b.y + (0.5 * b.width) && y + (0.5 * width) >= b.y - (0.5 * b.width));
  }

  bool box::intersects(box&& b)
  {
    return (x - (0.5 * width) <= b.x + (0.5 * b.width) && x + (0.5 * width) >= b.x - (0.5 * b.width)) &&
           (y - (0.5 * width) <= b.y + (0.5 * b.width) && y + (0.5 * width) >= b.y - (0.5 * b.width));
  }
}

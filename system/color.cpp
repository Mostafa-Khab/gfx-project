#include "color.hpp"

namespace gfx
{

  rgb::rgb(float _r, float _g, float _b)
    :r(_r), g(_g), b(_b)
  {

  }

  rgba::rgba(float _r, float _g, float _b, float _a)
    :r(_r), g(_g), b(_b), a(_a)
  {

  }

  rgba hex(unsigned int color)
  {
    // r = (color >> 24) & 0xff;
    // g = (color >> 16) & 0xff;
    // b = (color >> 8 ) & 0xff;
    // a = (color) & 0xff;

    return rgba(
        ((color >> 24) & 0xff) / 255.f,
        ((color >> 16) & 0xff) / 255.f,
        ((color >> 8 ) & 0xff) / 255.f,
        ((color) & 0xff) / 255.f      
        );
  }

}


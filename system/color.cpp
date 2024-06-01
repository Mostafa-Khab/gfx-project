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

  rgba::rgba(rgb c, float _a)
    :r(c.r), g(c.g), b(c.b), a(_a)
  {

  }

  rgba hex(unsigned int color)
  {
    return rgba(
        ((color >> 24) & 0xff) / 255.f,
        ((color >> 16) & 0xff) / 255.f,
        ((color >> 8 ) & 0xff) / 255.f,
        ((color) & 0xff) / 255.f      
        );
  }

  rgba gruv::red    = gfx::hex(0xcc241dff);
  rgba gruv::green  = gfx::hex(0x98971aff);
  rgba gruv::yellow = gfx::hex(0xd79921ff);
  rgba gruv::blue   = gfx::hex(0x458588ff);
  rgba gruv::purple = gfx::hex(0xb16286ff);
  rgba gruv::aqua   = gfx::hex(0x689d6aff);
  rgba gruv::orange = gfx::hex(0xd65d0eff);

  rgba gruv::white  = gfx::hex(0xebdbb2ff);
  rgba gruv::gray   = gfx::hex(0x928374ff);
  rgba gruv::black  = gfx::hex(0x282828ff);
}


/************************* 
 *  author : mostafa khaled 
 *  date   : Sat Feb 10 09:24:56 PM EET 2024
 *  why    : deal with colors
*************************/ 
#ifndef COLOR_HPP
#define COLOR_HPP

namespace gfx{

  struct rgb
  {
    public:
      rgb(float _r, float _g, float _b);

    public:
    float r, g, b;
  };

  struct rgba
  {
    public:
      rgba(float _r, float _g, float _b, float _a);

    public:
    float r, g, b, a;
  };

}
#endif

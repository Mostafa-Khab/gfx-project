/************************* 
 *  author : mostafa khaled 
 *  date   : Sat Feb 10 09:24:56 PM EET 2024
 *  why    : deal with colors
*************************/ 
#ifndef COLOR_HPP
#define COLOR_HPP

namespace gfx{

  struct rgba;

  struct rgb
  {
    public:
      rgb(float _r, float _g, float _b);
      rgb(rgba c);

      rgb hex(unsigned int color);
    public:
    float r, g, b;
  };

  struct rgba
  {
    public:
      rgba(float _r, float _g, float _b, float _a);
      rgba(rgb c, float alpha = 1.f);

    public:
    float r, g, b, a;
  };

  rgba hex(unsigned int color);

  //adding a gruvbox color palette. (this is nice I think)

  struct gruv 
  {
    static rgba red;
    static rgba green;
    static rgba yellow;
    static rgba blue;
    static rgba purple;
    static rgba aqua;
    static rgba orange;

    static rgba white;
    static rgba gray;
    static rgba black;
  };
}
#endif

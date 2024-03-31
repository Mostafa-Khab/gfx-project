/************************* 
 *  author : mostafa khaled 
 *  date   : Sat Feb 10 09:24:56 PM EET 2024
 *  why    : deal with colors
*************************/ 
#ifndef COLOR_HPP
#define COLOR_HPP

struct RGB
{
  public:
    RGB(float _r, float _g, float _b);

  public:
  float r, g, b;
};

struct RGBA
{
  public:
    RGBA(float _r, float _g, float _b, float _a);

  public:
  float r, g, b, a;
};
#endif

/*********************************
 * author     : mostafa khaled
 * date       : Sun May 26 11:21:28 AM EEST 2024
 * desc       : 
 ********************************/
#ifndef BOX_HPP
#define BOX_HPP


namespace gfx 
{
  template <typename T> struct vector2;

  struct box 
  {
    //NOTE: this position is the center of the box
    float x, y, width, height;

    bool intersects(const box& b);
    bool intersects(box&& b);
  };
}

#endif /* !BOX_HPP */

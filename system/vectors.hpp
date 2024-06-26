/************************* 
 *  author : mostafa khaled 
 *  data   : Sat Feb 10 09:14:26 PM EET 2024
 *  why    : ease dealing with vectors in c++
 *  NOTE   : this is in very early development
*************************/ 
#ifndef VECTORS_HPP
#define VECTORS_HPP

namespace gfx
{

  template <typename T>
  struct vector2
  {
    public:
      explicit vector2(T x, T y);
      vector2(const vector2<T>& another) = default;
      vector2(vector2<T>&& another) = default;
      ~vector2() = default;

      vector2<T>& operator= (const vector2<T>& another) = default;
      vector2<T>  operator+ (const vector2<T>& another);
      vector2<T>  operator- (const vector2<T>& another);

      float  distance  (const vector2<T>& another);

    public:
      T x, y;
  };
  typedef vector2<float> vector2f;
  typedef vector2<int> vector2i;

  template <typename T>
  struct vector3
  {
    public:
      explicit vector3(T x, T y, T z);
      vector3(const vector3<T>& another) = default;
      vector3(vector3<T>&& another) = default;
      ~vector3() = default;

      vector3<T>& operator= (const vector3<T>& another) = default;
      vector3<T>  operator+ (const vector3<T>& another);
      vector3<T>  operator- (const vector3<T>& another);

      float  distance  (const vector3<T>& another);


    public:
      T x, y, z;
  };
  typedef vector3<float> vector3f;
  typedef vector3<int> vector3i;

}
#endif

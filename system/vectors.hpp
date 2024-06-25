/************************* 
 *  author : mostafa khaled 
 *  data   : Sat Feb 10 09:14:26 PM EET 2024
 *  why    : ease dealing with vectors in c++
 *  NOTE   : some errors occur after doing some shit
*************************/ 
#ifndef VECTORS_HPP
#define VECTORS_HPP

namespace std
{
  template <typename T> class function;
}

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
      vector2<T>  operator* (T num);

      float  distance  (const vector2<T>& another);

      struct attributes;
      static void set_attributes();
    public:
      T x, y;
  };

  template <typename T>
  struct vector2<T>::attributes
  {
    static int& vpos_location() { static int val = 0; return val; }
  };

  typedef vector2<int> vector2i;
  typedef vector2<float> vector2f;
  typedef vector2<double> vector2d;

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
      vector3<T>  operator* (T num);

      float  distance  (const vector3<T>& another);

      struct attributes;
      static void set_attributes();

    public:
      T x, y, z;
  };

  template <typename T>
  struct vector3<T>::attributes
  {
    static int& vpos_location() { static int val = 0; return val; }
  };

  typedef vector3<float> vector3f;
  typedef vector3<int> vector3i;
  typedef vector3<double> vector3d;

  float derivate(std::function<float(float)> f, float x, float h = 0.0001);

}
#endif

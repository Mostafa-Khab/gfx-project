#include <cmath>
#include "vectors.hpp"

namespace gfx{

  template <typename T>
  vector2<T>::vector2(T _x, T _y): x(_x), y(_y)
  {

  }

  template <typename T>
  vector2<T> vector2<T>::operator+ (const vector2<T>& another)
  {
    return vector2<T>(this->x + another.x, this->y + another.y);
  }

  template <typename T>
  vector2<T> vector2<T>::operator- (const vector2<T>& another)
  {
    return vector2<T>(another.x - this->x, another.y - this->y);
  }

  template <typename T>
  float vector2<T>::distance(const vector2<T>& another)
  {
    vector2<T> temp = *this - another;
    return std::sqrt(temp.x * temp.x + temp.y * temp.y);
  }

  template <typename T>
  vector3<T>::vector3(T _x, T _y, T _z): x(_x), y(_y), z(_z)
  {

  }

  template <typename T>
  vector3<T> vector3<T>::operator+ (const vector3<T>& another)
  {
    return vector3<T>(this->x + another.x, this->y + another.y, this->z + another.z);
  }

  template <typename T>
  vector3<T> vector3<T>::operator- (const vector3<T>& another)
  {
    return vector3<T>(another.x - this->x, another.y - this->y, another.z - this->z);
  }

  template <typename T>
  float vector3<T>::distance(const vector3<T>& another)
  {
    vector3<T> temp = *this - another;
    return std::sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
  }

  template class vector2<float>;
  template class vector2<int>;

  template class vector3<float>;
  template class vector3<int>;
}

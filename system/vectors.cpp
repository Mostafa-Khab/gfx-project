#include <glad/gl.h>

#include <cmath>
#include <functional>
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
  vector2<T> vector2<T>::operator* (T num)
  {
    return vector2<T>(x * num, y * num);
  }

  template <typename T>
  float vector2<T>::distance(const vector2<T>& another)
  {
    vector2<T> temp = *this - another;
    return std::sqrt(temp.x * temp.x + temp.y * temp.y);
  }

  //remember to set vpos_location from your shader program!!
  template <typename T>
  void vector2<T>::set_attributes()
  {
    glEnableVertexAttribArray(attributes::vpos_location());
    glVertexAttribPointer(attributes::vpos_location(), 2, GL_FLOAT, GL_FALSE, sizeof(vector2<T>), (void*)(0));
  }

  /************************* vector3 *************************/
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
  vector3<T> vector3<T>::operator* (T num)
  {
    return vector3<T>(x * num, y * num, z * num);
  }

  template <typename T>
  float vector3<T>::distance(const vector3<T>& another)
  {
    vector3<T> temp = *this - another;
    return std::sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
  }

  //remember to set vpos_location from your shader program!!
  template <typename T>
  void vector3<T>::set_attributes()
  {
    glEnableVertexAttribArray(attributes::vpos_location());
    glVertexAttribPointer(attributes::vpos_location(), 3, GL_FLOAT, GL_FALSE, sizeof(vector3<T>), (void*)(0));
  }

  float derivate(std::function<float(float)> f, float x, float h)
  {

    return (f(x + h) - f(x - h)) / (2.f * h);
  }

  template class vector2<double>;
  template class vector2<float>;
  template class vector2<int>;

  template class vector3<double>;
  template class vector3<float>;
  template class vector3<int>;
}

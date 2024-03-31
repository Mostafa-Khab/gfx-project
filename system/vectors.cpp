#include <cmath>
#include "vectors.hpp"

template <typename T>
Vector2<T>::Vector2(T _x, T _y): x(_x), y(_y)
{

}

template <typename T>
Vector2<T> Vector2<T>::operator+ (const Vector2<T>& another)
{
  return Vector2<T>(this->x + another.x, this->y + another.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator- (const Vector2<T>& another)
{
  return Vector2<T>(another.x - this->x, another.y - this->y);
}

template <typename T>
float Vector2<T>::distance(const Vector2<T>& another)
{
  Vector2<T> temp = *this - another;
  return std::sqrt(temp.x * temp.x + temp.y * temp.y);
}

template <typename T>
Vector3<T>::Vector3(T _x, T _y, T _z): x(_x), y(_y), z(_z)
{

}

template <typename T>
Vector3<T> Vector3<T>::operator+ (const Vector3<T>& another)
{
  return Vector3<T>(this->x + another.x, this->y + another.y, this->z + another.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator- (const Vector3<T>& another)
{
  return Vector3<T>(another.x - this->x, another.y - this->y, another.z - this->z);
}

template <typename T>
float Vector3<T>::distance(const Vector3<T>& another)
{
  Vector3<T> temp = *this - another;
  return std::sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
}

template class Vector2<float>;
template class Vector2<int>;

template class Vector3<float>;
template class Vector3<int>;

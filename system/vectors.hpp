/************************* 
 *  author : mostafa khaled 
 *  data   : Sat Feb 10 09:14:26 PM EET 2024
 *  why    : ease dealing with vectors in c++
 *  NOTE   : this is in very early development
*************************/ 
#ifndef VECTORS_HPP
#define VECTORS_HPP

template <typename T>
struct Vector2
{
  public:
    explicit Vector2(T x, T y);
    Vector2(const Vector2<T>& another) = default;
    Vector2(Vector2<T>&& another) = default;
    ~Vector2() = default;

    Vector2<T>& operator= (const Vector2<T>& another) = default;
    Vector2<T>  operator+ (const Vector2<T>& another);
    Vector2<T>  operator- (const Vector2<T>& another);

    float  distance  (const Vector2<T>& another);


  public:
    T x, y;
};
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

template <typename T>
struct Vector3
{
  public:
    explicit Vector3(T x, T y, T z);
    Vector3(const Vector3<T>& another) = default;
    Vector3(Vector3<T>&& another) = default;
    ~Vector3() = default;

    Vector3<T>& operator= (const Vector3<T>& another) = default;
    Vector3<T>  operator+ (const Vector3<T>& another);
    Vector3<T>  operator- (const Vector3<T>& another);

    float  distance  (const Vector3<T>& another);


  public:
    T x, y, z;
};
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

#endif

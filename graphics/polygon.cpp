#include <cmath>
#include <glad/gl.h>
#include "vertex.hpp"
#include "buffer.hpp"
#include "polygon.hpp"


template <typename T>
Polygon<T>::Polygon(int sides, float r)
  :m_radius(r), m_rotation(0.f), m_sides(sides)
{ }

#define PI 3.1415926

template<typename T>
void Polygon<T>::generate_buffer_data()
{
  const float angle = (PI * 2) / m_sides;
  T           data  = m_data;
  const float rotation = m_rotation * PI / 180;

  for(int i = 0; i < m_sides; ++i)
  {
    data.x = (m_data.x + (m_radius * std::cos(angle * i + rotation)));
    data.y = (m_data.y + (m_radius * std::sin(angle * i + rotation)));

    m_vertices.append(data);
  }
}

template<typename T>
void Polygon<T>::create_using_data(GLenum usage)
{
  generate_buffer_data();
  bind();
  load_data(usage);
}

template<typename T>
void Polygon<T>::get_data(Buffer<T>& vertices)
{
  auto size = m_vertices.size();
  for(int i = 0; i < size; ++i)
  {
    vertices.append(m_vertices[i]);
  }
}

template<typename T>
void Polygon<T>::load_data(GLenum usage)
{
  m_vertices.load_data(usage);
}

template<typename T>
void Polygon<T>::bind()
{
  m_vertices.bind();
}

template<typename T>
void Polygon<T>::unbind()
{
  m_vertices.unbind();
}

template<typename T>
void Polygon<T>::setRadius(float r)
{
  m_radius = r;
}

template<typename T>
void Polygon<T>::setRotation(float angle)
{
  m_rotation = angle;
}

template<typename T>
void Polygon<T>::setSides(int sides)
{
  m_sides = sides;
}

template<typename T>
void Polygon<T>::setData(T data)
{
  m_data = data;
}

template<typename T>
void Polygon<T>::draw(GLenum usage)
{
  m_vertices.draw(usage);
}

template class Polygon<Vertex>;
template class Polygon<VertexEx>;
template class Polygon<texVertex>;
template class Polygon<texVertexNoRGB>;

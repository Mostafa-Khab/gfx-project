#include <cmath>
#include <glad/gl.h>
#include "vertex.hpp"
#include "buffer.hpp"
#include "polygon.hpp"

namespace gfx
{

  template <typename T>
  polygon<T>::polygon(int sides, float r)
    :m_radius(r), m_rotation(0.f), m_sides(sides)
  { }

#define PI 3.1415926

  template<typename T>
  void polygon<T>::generate_buffer_data()
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
  void polygon<T>::create_using_data(int usage)
  {
    generate_buffer_data();
    bind();
    load_data(usage);
  }

  template<typename T>
  void polygon<T>::get_data(vbuffer<T>& vertices)
  {
    auto size = m_vertices.size();
    for(int i = 0; i < size; ++i)
    {
      vertices.append(m_vertices[i]);
    }
  }

  template<typename T>
  void polygon<T>::load_data(int usage)
  {
    m_vertices.load_data(usage);
  }

  template<typename T>
  void polygon<T>::bind()
  {
    m_vertices.bind();
  }

  template<typename T>
  void polygon<T>::unbind()
  {
    m_vertices.unbind();
  }

  template<typename T>
  void polygon<T>::setRadius(float r)
  {
    m_radius = r;
  }

  template<typename T>
  void polygon<T>::setRotation(float angle)
  {
    m_rotation = angle;
  }

  template<typename T>
  void polygon<T>::setSides(int sides)
  {
    m_sides = sides;
  }

  template<typename T>
  void polygon<T>::setData(T data)
  {
    m_data = data;
  }

  template<typename T>
  void polygon<T>::draw(int usage)
  {
    m_vertices.draw(usage);
  }

  template <typename T>
  T& polygon<T>::operator[] (std::size_t index)
  {
    return m_vertices[index];
  }

  template <typename T>
  std::size_t polygon<T>::size()
  {
    return m_vertices.size();
  }

  template <typename T>
  void polygon<T>::modify()
  {
    return m_vertices.modify();
  }

  template <typename T>
  void polygon<T>::remove()
  {
    return m_vertices.remove();
  }

  template class polygon<vertex2d>;
  template class polygon<vertex3d>;
  template class polygon<vertex3dtex>;
  template class polygon<vertex_tex>;
}

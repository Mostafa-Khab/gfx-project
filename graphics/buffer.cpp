#include <glad/gl.h>
#include <typeinfo>

#include <debug.hpp>

#include "vertex.hpp"
#include "buffer.hpp"

namespace gfx
{

  template <typename T>
  buffer<T>::buffer()
  {
    if(typeid(T) == typeid(unsigned int))
    {
      m_type = INDEX;
    } else {
      m_type = VERTEX;
    }
    glGenBuffers(1, &m_id);
  }

  template <typename T>
  buffer<T>::~buffer()
  {
    remove();
  }

  template <typename T>
  void buffer<T>::append(T& data)
  {
    m_data.push_back(data);
  }

  template <typename T>
  void buffer<T>::append(T&& data)
  {
    m_data.push_back(data);
  }

  template <typename T>
  void buffer<T>::bind()
  {
    switch(m_type)
    {
      case VERTEX:
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        break;
      case INDEX:
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        break;
      case ELSE:
        break;
    }
  }
  template <typename T>
  void buffer<T>::unbind()
  {
    GLenum e = (m_type == VERTEX)? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER; 
    glBindBuffer(e, 0);
  }

  template <typename T>
  void buffer<T>::load_data(GLenum usage)
  {
    const T* pdata = &(m_data[0]);
    if(m_type == VERTEX)
    {
      glBufferData(GL_ARRAY_BUFFER,
                   sizeof(T) * m_data.size(),
                   pdata,
                   usage);
    } else {
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   sizeof(T) * m_data.size(),
                   pdata,
                   usage);
    }
  }

  template <typename T>
  void buffer<T>::modify()
  {
    GLenum buff = (m_type == VERTEX)? GL_ARRAY_BUFFER : 
                                 GL_ELEMENT_ARRAY_BUFFER;
    const T* pdata = &(m_data[0]);

    glBufferSubData(buff, 0, (sizeof(T) * m_data.size()),
                    pdata);
  }

  template <typename T>
  void buffer<T>::draw(GLenum primative)
  {
    switch(m_type)
    {
      case VERTEX:
        glDrawArrays(primative, 0, m_data.size());
        break;
      case INDEX:
        glDrawElements(primative, m_data.size(), GL_UNSIGNED_INT, 0);
        break;
      case ELSE:
        break;
    }
  }

  template <typename T>
  std::size_t buffer<T>::size()
  {
    return m_data.size();
  }

  template <typename T>
  T& buffer<T>::operator[] (std::size_t index)
  {
    return m_data[index];
  }

  template <typename T>
  void buffer<T>::resize(std::size_t size)
  {
    m_data.resize(size);
  }

  template <typename T>
  void buffer<T>::reserve(std::size_t size)
  {
    m_data.reserve(size);
  }

  template <typename T>
  void buffer<T>::remove()
  {
    if(!m_removed)
    {
      m_removed = true;
      glDeleteBuffers(1, &m_id);
      std::string buff = (m_type == INDEX)? "index" : "vertex";
      buff += " buffer";
      Log::debug("deleting " + buff);
    }
  }


  template <typename T>
  void vbuffer<T>::set_attributes()
  {
    T::set_attributes();
  }

  template <typename T>
  void vbuffer<T>::draw(GLenum primative)
  {
    this->bind();
    this->set_attributes();

    buffer<T>::draw(primative);
  }


  template class buffer<vertex2d>;
  template class buffer<vertex3d>;
  template class buffer<vertex3dtex>;
  template class buffer<vertex_tex>;

  template class vbuffer<vertex2d>;
  template class vbuffer<vertex3d>;
  template class vbuffer<vertex3dtex>;
  template class vbuffer<vertex_tex>;

  template class buffer<unsigned int>;

}

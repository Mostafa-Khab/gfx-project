#include <glad/gl.h>

#include <typeinfo>

#include "../system/debug.hpp"

#include "../system/vectors.hpp"
#include "../system/box.hpp"
#include "vertex.hpp"
//#include "buffer.hpp"

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

  template<typename T>
  buffer<T>::buffer(const buffer<T>& buff)
    :m_id(buff.m_id), m_type(buff.m_type), m_removed(buff.m_removed), m_data(buff.m_data)
  {
    
  }

  template <typename T>
  buffer<T>::~buffer()
  {
    remove();
  }

  template <typename T>
  void buffer<T>::append(const T& data)
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

  //still need modifications
  template <typename T>
  void buffer<T>::modify(int si, int n)
  {
    if(n <= 0)
      n = m_data.size();

    if(si < 0 || si + n > m_data.size())
      Log::error("buffer<T>::modify is using starting index out of range [0 ~ m_data.size()-n]");

    GLenum buff = (m_type == VERTEX)? GL_ARRAY_BUFFER : 
                                 GL_ELEMENT_ARRAY_BUFFER;

    const T* pdata = &(m_data[si]);

    this->bind();

    //here!
    glBufferSubData(buff, 0 , (sizeof(T) * n), pdata);

    //glBufferSubData(buff, 0, (sizeof(T) * m_data.size()), pdata);
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
  std::size_t buffer<T>::size() const
  {
    return m_data.size();
  }

  template <typename T>
  T& buffer<T>::operator[] (std::size_t index)
  {
    return m_data[index];
  }

  template <typename T>
  buffer<T>& buffer<T>::operator= (const buffer<T>& buff)
  {
    m_id = buff.m_id;
    m_type = buff.m_type;
    m_removed = buff.m_removed;
    m_data = buff.m_data;
    return (*this);
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
  void buffer<T>::clear()
  {
    return m_data.clear();
  }

  //NOTE: a vbuffer can only have a vertex type and not unsigned int.
  //since all vertcies must have coorinates. we use the vertex to provide the other data as colors.
  template <typename T>
  void vbuffer<T>::append(box b, T v, bool strip)
  {
    v.x = b.x - (0.5 * b.width);
    v.y = b.y - (0.5 * b.height);
    buffer<T>::append(v);

    v.x = b.x + (0.5 * b.width);
    v.y = b.y - (0.5 * b.height);
    buffer<T>::append(v);

    v.x = b.x - (0.5 * b.width);
    v.y = b.y + (0.5 * b.height);
    buffer<T>::append(v);

    if(!strip)
    {
      v.x = b.x + (0.5 * b.width);
      v.y = b.y - (0.5 * b.height);
      buffer<T>::append(v);

      v.x = b.x - (0.5 * b.width);
      v.y = b.y + (0.5 * b.height);
      buffer<T>::append(v);
    }

    v.x = b.x + (0.5 * b.width);
    v.y = b.y + (0.5 * b.height);
    buffer<T>::append(v);
  }
  
  //I think you should run modify() after calling this function.
  template <typename T>
  void vbuffer<T>::move(vector2f v, int si, int ei)
  {
    if(si < 0 || si >= this->size() || ei < 0 || ei >= this->size())
    {
      Log::error("vbuffer move start index or end index must be in range [0-vbuffer.size()]");
      Log::error("vbuffer<T>::move() failed");
      return;
    }
    if(ei == 0)
      ei = this->size();
    for(int i = 0; i < this->size(); ++i)
    {
      (*this)[i].x += v.x;
      (*this)[i].y += v.y;
    }
  }

  template <typename T>
  void vbuffer<T>::update_box(box b, int i, bool strip)
  {

    if(strip)
    {
      (*this)[i].x     = b.x - (b.width / 2);
      (*this)[i].y     = b.y - (b.height / 2);

      (*this)[i + 1].x = b.x + (b.width / 2);
      (*this)[i + 1].y = b.y - (b.height / 2);

      (*this)[i + 2].x = b.x - (b.width / 2);
      (*this)[i + 2].y = b.y + (b.height / 2);

      (*this)[i + 3].x = b.x + (b.width / 2);
      (*this)[i + 3].y = b.y + (b.height / 2);

      return;
    }

    (*this)[i].x     = b.x - (b.width / 2);
    (*this)[i].y     = b.y - (b.height / 2);

    (*this)[i + 1].x = b.x + (b.width / 2);
    (*this)[i + 1].y = b.y - (b.height / 2);

    (*this)[i + 2].x = b.x - (b.width / 2);
    (*this)[i + 2].y = b.y + (b.height / 2);

      (*this)[i + 3].x = (*this)[i + 1].x;
      (*this)[i + 3].y = (*this)[i + 1].y;

      (*this)[i + 4].x = (*this)[i + 2].x;
      (*this)[i + 4].y = (*this)[i + 2].y;

    (*this)[i + 5].x = b.x + (b.width / 2);
    (*this)[i + 5].y = b.y + (b.height / 2);

  }

  template <typename T>
  void vbuffer<T>::modify_box(box b, int i, bool strip)
  {
    update_box(b, i, strip);

    if(strip)
      this->modify(i, 4);
    else
      this->modify(i, 6);

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

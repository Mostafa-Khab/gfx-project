/************************* 
 *  author : mostafa khaled 
 *  date   : Tue Feb  6 10:23:44 PM EET 2024
 *  why    : ease dealing with vertex buffers;
*************************/ 

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>

namespace gfx
{

  struct vertex2d;
  struct vertex3d;
  struct vertex3dtex;

  template <typename T>
  class buffer
  {
    public:
      enum Type { VERTEX, INDEX, ELSE };
    public:
      buffer();
      virtual ~buffer();

      void append(T& );
      void append(T&&);
      void resize(std::size_t size);
      void reserve(std::size_t size);
      void remove();

      void bind();
      void unbind();
      void load_data(GLenum usage = GL_STATIC_DRAW);  //based on the data provided in the vector of vertices.
      void modify();  //modify based in m_data. update data in m_data then call this to update. GL_DYNAMIC_DRAW


      virtual void draw(GLenum primative = GL_TRIANGLES);

      std::size_t size();

      T& operator[] (std::size_t index);

    protected:
      unsigned int    m_id;
      std::vector<T>  m_data;
      Type            m_type;
      bool            m_removed;

    public:
      friend class context;

  };

  template<typename T>
  class vbuffer: public buffer<T>
  {
    public:
      vbuffer(): buffer<T>() { }
      ~vbuffer() = default;
      void set_attributes();
      void draw(GLenum primative = GL_TRIANGLES) override;
  };

  typedef vbuffer<vertex2d>       vertex2d_buf;
  typedef vbuffer<vertex3d>       vertex3d_buf;
  typedef vbuffer<vertex3dtex>    vertex3dtex_buf;

  typedef buffer<unsigned int>    index_buf;

}
#endif

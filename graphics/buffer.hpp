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

  struct box;
  template <typename T> struct vector2;

  template <typename T>
  class buffer
  {
    public:
      enum Type { VERTEX, INDEX, ELSE };
    public:
      buffer();
      virtual ~buffer();

      buffer(const buffer& buff);

      void append(const T& );
      void append(T&&);

      void resize(std::size_t size);
      void reserve(std::size_t size);
      void remove();

      void bind();
      void unbind();
      void load_data(GLenum usage = GL_STATIC_DRAW);  //based on the data provided in the vector of vertices.
      void modify();  //modify based in m_data. update data in m_data then call this to update. GL_DYNAMIC_DRAW


      virtual void draw(GLenum primative = GL_TRIANGLES);

      std::size_t size() const;

      T& operator[] (std::size_t index);
      buffer& operator= (const buffer& buff);

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

      void append(box b, T v, bool strip);

      template <typename U>
      void append(U data)
      {
        buffer<T>::append(data);
      }

      void move(vector2<float> v);

      //if strip equals true, then only 4 vertcies are added.
      void modify_box(box b, int start_index = 0, bool strip = true);

      void set_attributes();
      void draw(GLenum primative = GL_TRIANGLES) override;
  };

  typedef vbuffer<vertex2d>       vertex2d_buf;
  typedef vbuffer<vertex3d>       vertex3d_buf;
  typedef vbuffer<vertex3dtex>    vertex3dtex_buf;

  typedef buffer<unsigned int>    index_buf;

}
#endif

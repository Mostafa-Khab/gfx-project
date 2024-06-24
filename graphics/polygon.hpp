/*********************************
 * author     : mostafa khaled
 * date       : Fri Mar 15 11:00:51 PM EET 2024
 * desc       : 
 * NOTE       : as this class is a template. a polgon will carry a vertex of the template type that has the data used                in the polygon
 ********************************/
#ifndef POLYGON_HPP
#define POLYGON_HPP

//GL_TRIANGLES           0x0004
//GL_STATIC_DRAW         0x88E4

namespace gfx
{

  template <typename T>
  class polygon
  {
    public:
      explicit polygon(int sides , float radius);
      ~polygon() = default;

      void generate_buffer_data();
      void create_using_data(int usage = 0x88E4);
      
      void load_data(int usage = 0x88E4);
      void bind();
      void unbind();

      void setRadius(float radius);
      void setRotation(float angle);
      void setSides(int sides);
      void setData(T data);

      void draw(int primative = GL_TRIANGLE_FAN);

      void get_data(vbuffer<T>& verticies);
      T& operator[] (std::size_t index);
      
      std::size_t size();
      void modify();
      void remove();

    private:
      float      m_radius;
      float      m_rotation;
      int        m_sides;
      T          m_data;     //Vertex Type that carries position and color data.
      vbuffer<T> m_vertices;

  };

}

#endif /* !POLYGON_HPP */

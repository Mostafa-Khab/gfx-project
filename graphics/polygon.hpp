/*********************************
 * author     : mostafa khaled
 * date       : Fri Mar 15 11:00:51 PM EET 2024
 * desc       : 
 * NOTE       : as this class is a template. a polgon will carry a vertex of the template type that has the data used                in the polygon
 ********************************/
#ifndef POLYGON_HPP
#define POLYGON_HPP

template <typename T>
class Polygon
{
  public:
    explicit Polygon(int sides , float radius);
    ~Polygon() = default;

    void generate_buffer_data();
    void create_using_data(GLenum usage = GL_STATIC_DRAW);
    
    void load_data(GLenum usage = GL_STATIC_DRAW);
    void bind();
    void unbind();

    void setRadius(float radius);
    void setRotation(float angle);
    void setSides(int sides);
    void setData(T data);

    void draw(GLenum primative = GL_TRIANGLE_FAN);

    void get_data(Buffer<T>& verticies);
    T& operator[] (std::size_t index);
    
    std::size_t size();
    void modify();
    void remove();

  private:
    float     m_radius;
    float     m_rotation;
    int       m_sides;
    T         m_data; //a Vertex Type that carry position and color data.
    vBuffer<T> m_vertices;

};

#endif /* !POLYGON_HPP */

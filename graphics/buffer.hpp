/************************* 
 *  author : mostafa khaled 
 *  date   : Tue Feb  6 10:23:44 PM EET 2024
 *  why    : ease dealing with vertex buffers;
*************************/ 

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>

struct Vertex;
struct VertexEx;
struct texVertex;

template <typename T>
class Buffer
{
  public:
    enum Type { VERTEX, INDEX, ELSE };
  public:
    Buffer();
    virtual ~Buffer();

    void append(T& );
    void append(T&&);
    void resize(std::size_t size);
    void reserve(std::size_t size);

    void bind();
    void unbind();  //do nothing till now
    void load_data(GLenum usage = GL_STATIC_DRAW);  //based on the data provided in the vector of vertices.
    void modify();  //modify based in m_data. update data in m_data then call this to update. GL_DYNAMIC_DRAW


    virtual void draw(GLenum primative = GL_TRIANGLES);

    std::size_t size();

    T& operator[] (std::size_t index);

  protected:
    unsigned int    m_id;
    std::vector<T>  m_data;
    Type            m_type;

  public:
    friend class Context;

};

template<typename T>
class vBuffer: public Buffer<T>
{
  public:
    vBuffer(): Buffer<T>() { }
    ~vBuffer() = default;
    void set_attributes();
    void draw(GLenum primative = GL_TRIANGLES) override;
};

typedef vBuffer<Vertex>       Vertex2Buffer;
typedef vBuffer<VertexEx>     Vertex3Buffer;
typedef vBuffer<texVertex>    TexVertex3Buffer;
typedef Buffer<unsigned int> IndexBuffer;

#endif

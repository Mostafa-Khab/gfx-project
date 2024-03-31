/************************* 
 *  author : mostafa khaled 
 *  date   : Tue Feb  6 10:37:01 PM EET 2024
*************************/ 

#ifndef VERTEX_HPP
#define VERTEX_HPP

struct RGB;
struct RGBA;

template <typename T> class Vector2;
template <typename T> class Vector3;

class Attributes
{
  public:
    static int& vpos_location() {static int loc; return loc; }
    static int& vcol_location() {static int loc; return loc; }
    static int& vtex_location() {static int loc; return loc; }
};

struct Vertex
{
  float x, y, r, g, b;

  Vertex() = default;
  Vertex(float x, float y, float r, float g, float b);
  Vertex(float x, float y, RGB color);
  Vertex(Vector2<float> , RGB color);
 ~Vertex() = default;

  Vertex(const Vertex& ) = default;
  Vertex(Vertex&&)       = default;

  Vertex& operator= (const Vertex& );
  Vertex& operator= (Vertex&&);

  static void set_attributes();
  
};

struct VertexEx
{
  float x, y, z, r, g, b, a;

  VertexEx() = default;
  VertexEx(float x, float y, float z, float r, float g, float b, float a);
  VertexEx(float x, float y, float z, RGBA color);
  VertexEx(Vector3<float> , RGBA color);
 ~VertexEx() = default;

  VertexEx(const VertexEx& ) = default;
  VertexEx(VertexEx&&)       = default;

  VertexEx& operator= (const VertexEx& );
  VertexEx& operator= (VertexEx&&);
  
  static void set_attributes();
};

struct texVertex
{
  float x, y, z, r, g, b, a, u, v;

  texVertex() = default;
  texVertex(float x, float y, float z, float r, float g, float b, float a, float u, float v);
  texVertex(float x, float y, float z, RGBA color, Vector2<float> tex_coords);
  texVertex(Vector3<float> , RGBA color, Vector2<float> tex_coords);
 ~texVertex() = default;

  texVertex(const texVertex& ) = default;
  texVertex(texVertex&&)       = default;

  texVertex& operator= (const texVertex& );
  texVertex& operator= (texVertex&&);
  
  static void set_attributes();
};


struct texVertexNoRGB
{
  float x, y, z, u, v;

  texVertexNoRGB() = default;
  texVertexNoRGB(float x, float y, float z, float u, float v);
  texVertexNoRGB(float x, float y, float z, Vector2<float> tex_coords);
  texVertexNoRGB(Vector3<float> , Vector2<float> tex_coords);
 ~texVertexNoRGB() = default;

  texVertexNoRGB(const texVertexNoRGB& ) = default;
  texVertexNoRGB(texVertexNoRGB&&)       = default;

  texVertexNoRGB& operator= (const texVertexNoRGB& );
  texVertexNoRGB& operator= (texVertexNoRGB&&);
  
  static void set_attributes();
};

typedef Vertex          Vertex2D;
typedef VertexEx        Vertex3D;
typedef texVertex       RGB_TexVertex3D; 
typedef texVertexNoRGB  TexVertex3D;

#endif

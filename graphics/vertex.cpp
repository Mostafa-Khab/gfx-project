#include <glad/gl.h>
#include "../system/color.hpp"
#include "../system/vectors.hpp"
#include "vertex.hpp"

Vertex::Vertex(float _x, float _y,
               float _r, float _g, float _b
              )
:x(_x), y(_y), r(_r), g(_g), b(_b)
{

}

Vertex::Vertex(float _x, float _y, RGB rgb)
  :x(_x), y(_y), r(rgb.r), g(rgb.g), b(rgb.b)
{

}

Vertex::Vertex(Vector2f v, RGB rgb)
  :x(v.x), y(v.y), r(rgb.r), g(rgb.g), b(rgb.b)
{

}

Vertex& Vertex::operator= (const Vertex& v)
{
  x = v.x;
  y = v.y;
  
  r = v.r;
  g = v.g;
  b = v.b;

  return (*this);

}

Vertex& Vertex::operator= (Vertex&& v)
{
  x = v.x;
  y = v.y;
  
  r = v.r;
  g = v.g;
  b = v.b;

  return (*this);

}

void Vertex::set_attributes()
{
  glEnableVertexAttribArray(Attributes::vpos_location());
  glVertexAttribPointer(Attributes::vpos_location(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));

  glEnableVertexAttribArray(Attributes::vcol_location());
  glVertexAttribPointer(Attributes::vcol_location(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 2));
}

VertexEx::VertexEx(float _x, float _y, float _z,
               float _r, float _g, float _b, float _a
              )
:x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), a(_a)
{

}

VertexEx::VertexEx(float _x, float _y, float _z, RGBA rgba)
  :x(_x), y(_y), z(_z), r(rgba.r), g(rgba.g), b(rgba.b), a(rgba.a)
{

}

VertexEx::VertexEx(Vector3f v, RGBA rgba)
  :x(v.x), y(v.y), z(v.z), r(rgba.r), g(rgba.g), b(rgba.b), a(rgba.a)
{

}

VertexEx& VertexEx::operator= (const VertexEx& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  
  r = v.r;
  g = v.g;
  b = v.b;
  a = v.a;

  return (*this);

}

VertexEx& VertexEx::operator= (VertexEx&& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  
  r = v.r;
  g = v.g;
  b = v.b;
  a = v.a;

  return (*this);

}

void VertexEx::set_attributes()
{
  glEnableVertexAttribArray(Attributes::vpos_location());
  glVertexAttribPointer(Attributes::vpos_location(), 3, GL_FLOAT, GL_FALSE, sizeof(VertexEx), (void*)(0));

  glEnableVertexAttribArray(Attributes::vcol_location());
  glVertexAttribPointer(Attributes::vcol_location(), 4, GL_FLOAT, GL_FALSE, sizeof(VertexEx), (void*)(sizeof(float) * 3));
}

texVertex::texVertex(float _x, float _y, float _z,
               float _r, float _g, float _b, float _a,
               float _u, float _v
              )
:x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), a(_a), u(_u), v(_v)
{

}

texVertex::texVertex(float _x, float _y, float _z, RGBA rgba, Vector2f uv)
  :x(_x), y(_y), z(_z), r(rgba.r), g(rgba.g), b(rgba.b), a(rgba.a), u(uv.x), v(uv.y)
{

}

texVertex::texVertex(Vector3f v, RGBA rgba, Vector2f uv)
  :x(v.x), y(v.y), z(v.z), r(rgba.r), g(rgba.g), b(rgba.b), a(rgba.a), u(uv.x), v(uv.y)
{

}

texVertex& texVertex::operator= (const texVertex& vert)
{
  x = vert.x;
  y = vert.y;
  z = vert.z;
  
  r = vert.r;
  g = vert.g;
  b = vert.b;
  a = vert.a;

  u = vert.u;
  v = vert.v;

  return (*this);

}


texVertex& texVertex::operator= (texVertex&& vert)
{
  x = vert.x;
  y = vert.y;
  z = vert.z;
  
  r = vert.r;
  g = vert.g;
  b = vert.b;
  a = vert.a;

  u = vert.u;
  v = vert.v;
  return (*this);

}

void texVertex::set_attributes()
{
  glEnableVertexAttribArray(Attributes::vpos_location());
  glVertexAttribPointer(Attributes::vpos_location(), 3, GL_FLOAT, GL_FALSE, sizeof(texVertex), (void*)0);

  glEnableVertexAttribArray(Attributes::vcol_location());
  glVertexAttribPointer(Attributes::vcol_location(), 4, GL_FLOAT, GL_FALSE, sizeof(texVertex), (void*)(sizeof(float) * 3));

  glEnableVertexAttribArray(Attributes::vtex_location());
  glVertexAttribPointer(Attributes::vtex_location(), 2, GL_FLOAT, GL_FALSE, sizeof(texVertex), (void*)(sizeof(float) * 7));
}

texVertexNoRGB::texVertexNoRGB(float _x, float _y, float _z,
               float _u, float _v
              )
:x(_x), y(_y), z(_z), u(_u), v(_v)
{

}

texVertexNoRGB::texVertexNoRGB(float _x, float _y, float _z,Vector2f uv)
  :x(_x), y(_y), z(_z), u(uv.x), v(uv.y)
{

}

texVertexNoRGB::texVertexNoRGB(Vector3f v, Vector2f uv)
  :x(v.x), y(v.y), z(v.z), u(uv.x), v(uv.y)
{

}

texVertexNoRGB& texVertexNoRGB::operator= (const texVertexNoRGB& vert)
{
  x = vert.x;
  y = vert.y;
  z = vert.z;
  
  u = vert.u;
  v = vert.v;

  return (*this);

}

texVertexNoRGB& texVertexNoRGB::operator= (texVertexNoRGB&& vert)
{
  x = vert.x;
  y = vert.y;
  z = vert.z;
  
  u = vert.u;
  v = vert.v;
  return (*this);

}

void texVertexNoRGB::set_attributes()
{
  
  glEnableVertexAttribArray(Attributes::vpos_location());
  glVertexAttribPointer(Attributes::vpos_location(), 3, GL_FLOAT, GL_FALSE, sizeof(texVertexNoRGB), (void*)0);

  glEnableVertexAttribArray(Attributes::vtex_location());
  glVertexAttribPointer(Attributes::vtex_location(), 2, GL_FLOAT, GL_FALSE, sizeof(texVertexNoRGB), (void*)(sizeof(float) * 3));
}

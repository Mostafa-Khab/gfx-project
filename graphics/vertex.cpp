#include <glad/gl.h>
#include "../system/color.hpp"
#include "../system/vectors.hpp"
#include "vertex.hpp"

namespace gfx
{

  vertex2d::vertex2d(float _x, float _y,
                 float _r, float _g, float _b
                )
  :x(_x), y(_y), r(_r), g(_g), b(_b)
  {

  }

  vertex2d::vertex2d(float _x, float _y, rgb col)
    :x(_x), y(_y), r(col.r), g(col.g), b(col.b)
  {

  }

  vertex2d::vertex2d(vector2f v, rgb col)
    :x(v.x), y(v.y), r(col.r), g(col.g), b(col.b)
  {

  }

  vertex2d& vertex2d::operator= (const vertex2d& v)
  {
    x = v.x;
    y = v.y;
    
    r = v.r;
    g = v.g;
    b = v.b;

    return (*this);

  }

  vertex2d& vertex2d::operator= (vertex2d&& v)
  {
    x = v.x;
    y = v.y;
    
    r = v.r;
    g = v.g;
    b = v.b;

    return (*this);

  }

  void vertex2d::set_attributes()
  {
    glEnableVertexAttribArray(attributes::vpos_location());
    glVertexAttribPointer(attributes::vpos_location(), 2, GL_FLOAT, GL_FALSE, sizeof(vertex2d), (void*)(0));

    glEnableVertexAttribArray(attributes::vcol_location());
    glVertexAttribPointer(attributes::vcol_location(), 3, GL_FLOAT, GL_FALSE, sizeof(vertex2d), (void*)(sizeof(float) * 2));
  }

  vertex3d::vertex3d(float _x, float _y, float _z,
                 float _r, float _g, float _b, float _a
                )
  :x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), a(_a)
  {

  }

  vertex3d::vertex3d(float _x, float _y, float _z, rgba col)
    :x(_x), y(_y), z(_z), r(col.r), g(col.g), b(col.b), a(col.a)
  {

  }

  vertex3d::vertex3d(vector3f v, rgba col)
    :x(v.x), y(v.y), z(v.z), r(col.r), g(col.g), b(col.b), a(col.a)
  {

  }

  vertex3d& vertex3d::operator= (const vertex3d& v)
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

  vertex3d& vertex3d::operator= (vertex3d&& v)
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

  void vertex3d::set_attributes()
  {
    glEnableVertexAttribArray(attributes::vpos_location());
    glVertexAttribPointer(attributes::vpos_location(), 3, GL_FLOAT, GL_FALSE, sizeof(vertex3d), (void*)(0));

    glEnableVertexAttribArray(attributes::vcol_location());
    glVertexAttribPointer(attributes::vcol_location(), 4, GL_FLOAT, GL_FALSE, sizeof(vertex3d), (void*)(sizeof(float) * 3));
  }

  vertex3dtex::vertex3dtex(float _x, float _y, float _z,
                 float _r, float _g, float _b, float _a,
                 float _u, float _v
                )
  :x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), a(_a), u(_u), v(_v)
  {

  }

  vertex3dtex::vertex3dtex(float _x, float _y, float _z, rgba col, vector2f uv)
    :x(_x), y(_y), z(_z), r(col.r), g(col.g), b(col.b), a(col.a), u(uv.x), v(uv.y)
  {

  }

  vertex3dtex::vertex3dtex(vector3f v, rgba col, vector2f uv)
    :x(v.x), y(v.y), z(v.z), r(col.r), g(col.g), b(col.b), a(col.a), u(uv.x), v(uv.y)
  {

  }

  vertex3dtex& vertex3dtex::operator= (const vertex3dtex& vert)
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


  vertex3dtex& vertex3dtex::operator= (vertex3dtex&& vert)
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

  void vertex3dtex::set_attributes()
  {
    glEnableVertexAttribArray(attributes::vpos_location());
    glVertexAttribPointer(attributes::vpos_location(), 3, GL_FLOAT, GL_FALSE, sizeof(vertex3dtex), (void*)0);

    glEnableVertexAttribArray(attributes::vcol_location());
    glVertexAttribPointer(attributes::vcol_location(), 4, GL_FLOAT, GL_FALSE, sizeof(vertex3dtex), (void*)(sizeof(float) * 3));

    glEnableVertexAttribArray(attributes::vtex_location());
    glVertexAttribPointer(attributes::vtex_location(), 2, GL_FLOAT, GL_FALSE, sizeof(vertex3dtex), (void*)(sizeof(float) * 7));
  }

  vertex_tex::vertex_tex(float _x, float _y, float _z,
                 float _u, float _v
                )
  :x(_x), y(_y), z(_z), u(_u), v(_v)
  {

  }

  vertex_tex::vertex_tex(float _x, float _y, float _z,vector2f uv)
    :x(_x), y(_y), z(_z), u(uv.x), v(uv.y)
  {

  }

  vertex_tex::vertex_tex(vector3f v, vector2f uv)
    :x(v.x), y(v.y), z(v.z), u(uv.x), v(uv.y)
  {

  }

  vertex_tex& vertex_tex::operator= (const vertex_tex& vert)
  {
    x = vert.x;
    y = vert.y;
    z = vert.z;
    
    u = vert.u;
    v = vert.v;

    return (*this);

  }

  vertex_tex& vertex_tex::operator= (vertex_tex&& vert)
  {
    x = vert.x;
    y = vert.y;
    z = vert.z;
    
    u = vert.u;
    v = vert.v;
    return (*this);

  }

  void vertex_tex::set_attributes()
  {
    
    glEnableVertexAttribArray(attributes::vpos_location());
    glVertexAttribPointer(attributes::vpos_location(), 3, GL_FLOAT, GL_FALSE, sizeof(vertex_tex), (void*)0);

    glEnableVertexAttribArray(attributes::vtex_location());
    glVertexAttribPointer(attributes::vtex_location(), 2, GL_FLOAT, GL_FALSE, sizeof(vertex_tex), (void*)(sizeof(float) * 3));
  }

}

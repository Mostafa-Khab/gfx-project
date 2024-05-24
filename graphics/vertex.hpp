/************************* 
 *  author : mostafa khaled 
 *  date   : Tue Feb  6 10:37:01 PM EET 2024
*************************/ 

#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace gfx
{

  struct rgb;
  struct rgba;

  template <typename T> class vector2;
  template <typename T> class vector3;

  class attributes
  {
    public:
      static int& vpos_location() { static int val = 0; return val;}
      static int& vcol_location() { static int val = 0; return val;}
      static int& vtex_location() { static int val = 0; return val;}
  };

  struct vertex2d
  {
    float x, y, r, g, b;

    vertex2d() = default;
    vertex2d(float x, float y, float r, float g, float b);
    vertex2d(float x, float y, rgb color);
    vertex2d(vector2<float> , rgb color);
   ~vertex2d() = default;

    vertex2d(const vertex2d& ) = default;
    vertex2d(vertex2d&&)       = default;

    vertex2d& operator= (const vertex2d& );
    vertex2d& operator= (vertex2d&&);

    static void set_attributes();
    
  };

  struct vertex3d
  {
    float x, y, z, r, g, b, a;

    vertex3d() = default;
    vertex3d(float x, float y, float z, float r, float g, float b, float a);
    vertex3d(float x, float y, float z, rgba color);
    vertex3d(vector3<float> , rgba color);
   ~vertex3d() = default;

    vertex3d(const vertex3d& ) = default;
    vertex3d(vertex3d&&)       = default;

    vertex3d& operator= (const vertex3d& );
    vertex3d& operator= (vertex3d&&);
    
    static void set_attributes();
  };

  struct vertex3dtex
  {
    float x, y, z, r, g, b, a, u, v;

    vertex3dtex() = default;
    vertex3dtex(float x, float y, float z, float r, float g, float b, float a, float u, float v);
    vertex3dtex(float x, float y, float z, rgba color, vector2<float> tex_coords);
    vertex3dtex(vector3<float> , rgba color, vector2<float> tex_coords);
   ~vertex3dtex() = default;

    vertex3dtex(const vertex3dtex& ) = default;
    vertex3dtex(vertex3dtex&&)       = default;

    vertex3dtex& operator= (const vertex3dtex& );
    vertex3dtex& operator= (vertex3dtex&&);
    
    static void set_attributes();
  };


  struct vertex_tex
  {
    float x, y, z, u, v;

    vertex_tex() = default;
    vertex_tex(float x, float y, float z, float u, float v);
    vertex_tex(float x, float y, float z, vector2<float> tex_coords);
    vertex_tex(vector3<float> , vector2<float> tex_coords);
   ~vertex_tex() = default;

    vertex_tex(const vertex_tex& ) = default;
    vertex_tex(vertex_tex&&)       = default;

    vertex_tex& operator= (const vertex_tex& );
    vertex_tex& operator= (vertex_tex&&);
    
    static void set_attributes();
  };

}
//typedef vertex2d           Vertex2D;
//typedef vertex3d           Vertex3D;
//typedef vertex3dtex        RGB_TexVertex3D; 
//typedef vertex_tex         TexVertex3D;

#endif

/*********************************
 * author     : mostafa khaled
 * date       : Sat Jun  8 03:14:45 PM EEST 2024
 * desc       : 
 ********************************/
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace gfx
{
  //set the vtex_location in global attributes, and use proper shaders 3d_tex.
  class texture 
  {
    public:
      texture(int target = GL_TEXTURE_2D, int format = GL_RGB);
     ~texture();

      bool load(std::string path);
      void bind();
      void unbind();
      void create();

      void free_image();

      void remove();

      void dump(std::ostream& os);

    public:
      unsigned int id;
      int width, height, channels;
      unsigned char* data;
      int format;
    private:
      int target;
      bool freed, deleted;
  };
}

#endif /* !TEXTURE_HPP */

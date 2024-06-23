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

      //NOTE: the following  constructor copies the pointer. not the actual data. so the pointer must be valid before copying the 
      //texture to the GPU. d must be valid when calling texture::create();
      texture(int w, int h, int c, unsigned char* d, int target = GL_TEXTURE_2D, int format = GL_RGB);

      texture(const texture& t);
      texture(texture&& t);
     ~texture();

      bool load(std::string path);
      void bind();
      void unbind();
      void create();

      void free_image();

      void remove();

      void dump(std::ostream& os);

      //sometimes other things does free the pointer.
      void set_auto_free(bool free_this_image);

      texture& operator= (const texture& t);
      texture& operator= (texture&& t);

    public:
      unsigned int id;
      int width, height, channels;
      unsigned char* data;
      int format;
    private:
      int target;
      bool freed, deleted;
      bool auto_free;
  };
}

#endif /* !TEXTURE_HPP */

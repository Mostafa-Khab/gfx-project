#include <glad/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>
#include <iostream>

#include <logger.hpp>

#include "texture.hpp"

namespace gfx
{

  texture::texture(int t, int f)
    :id(0), target(t), freed(false), deleted(false), format(f)
  {
    glGenTextures(1, &id);
  }

  texture::~texture()
  {
    if(!freed)
      free_image();

    remove();

  }

  bool texture::load(std::string path)
  {
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if(!data) Log::error("failed to load requested image");
    return data != nullptr;
  }

  void texture::bind()
  {
    glBindTexture(target, id);
  }

  void texture::unbind()
  {
    glBindTexture(target, 0);
  }

  void texture::create()
  {
    glBindTexture(target, id);
    glTexImage2D(target, 0, format, width, height, 0 , format, GL_UNSIGNED_BYTE, data);


    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST
    glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }

  void texture::free_image()
  {
    if(data)
    {
      stbi_image_free(data);
      data = nullptr;
      freed = true;
    }
  }

  void texture::remove()
  {
    if(!deleted)
    {
      glDeleteTextures(1, &id);
      deleted = true;
    }
  }

  void texture::dump(std::ostream& os)
  {
    for(unsigned int i = 0; i < (width * height * channels) - 1; ++i)
    {
      unsigned int color = data[i];

      if(i % channels == 0)
        os << ' ';

      if(!color)
        os << color << color;
      else
        os << std::hex << color;
    }
    os << '\n';
  }

}

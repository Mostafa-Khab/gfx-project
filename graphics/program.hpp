/************************* 
 *  author : mostafa khaled 
 *  date   : Wed Feb  7 11:37:51 AM EET 2024
 *  why    : shader program wrapper
*************************/ 

#include "shader.hpp"

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

namespace gfx
{


  class program
  {
    public:
      program();
     ~program();

      void attachShaders(shader& vertex_shader, shader& fragment_shader);
      void link();
      void use();
      void remove();

      //remember to call link after reloading.
      void reload(std::string vshader_file, std::string fshader_file);

      bool create(std::string vshader_file, std::string fshader_file);

      int getUniformLocation(const char* name_in_program);
      int getAttribLocation(const char* name_in_program);

    private:
      unsigned int      m_id;
      bool              m_removed = false;
  };

  //bool create_glsl_program(program& program, std::string vshader_file, std::string fshader_file);

}
#endif

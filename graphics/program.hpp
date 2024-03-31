/************************* 
 *  author : mostafa khaled 
 *  date   : Wed Feb  7 11:37:51 AM EET 2024
 *  why    : shader program wrapper
*************************/ 

#include "shader.hpp"

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

class Program
{
  public:
    Program();
   ~Program();

    void attachShaders(Shader& vertex_shader, Shader& fragment_shader);
    void link();
    void use();

    int getUniformLocation(const char* name_in_program);
    int getAttribLocation(const char* name_in_program);

  private:
    unsigned int      m_id;
};

bool create_glsl_program(Program& program, std::string vshader_file, std::string fshader_file);

#endif

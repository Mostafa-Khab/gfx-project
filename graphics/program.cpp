#include <glad/gl.h>
#include "../system/debug.hpp"
#include "program.hpp"

Program::Program()
{
  m_id = glCreateProgram();
}

Program::~Program()
{
  glDeleteProgram(m_id);
}

void Program::attachShaders(Shader& vertex, Shader& frag)
{
  glAttachShader(m_id, vertex.getID());
  glAttachShader(m_id, frag.getID());
}

void Program::link()
{
  glLinkProgram(m_id);
}

void Program::use()
{
  glUseProgram(m_id);
}

int Program::getUniformLocation(const char* name)
{
  return glGetUniformLocation(m_id, name);
}

int Program::getAttribLocation(const char* name)
{
  return glGetAttribLocation(m_id, name);
}

bool create_glsl_program(Program& program, std::string vshader_file, std::string fshader_file)
{
  Shader vshader(Shader::Type::VERTEX);
  bool result = vshader.load(vshader_file);
  if(!result)
  {
    test::dprint("failed to load vertex shader\n");
    return false;
  }
  vshader.create();

  Shader fshader(Shader::Type::FRAGMENT);
  result = fshader.load(fshader_file);
  if(!result)
  {
    test::dprint("failed to load fragment shader\n");
    return false;
  }
  fshader.create();

  program.attachShaders(vshader, fshader);

  return true;
}

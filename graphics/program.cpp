#include <glad/gl.h>
#include <debug.hpp>
#include "program.hpp"

Program::Program()
{
  m_id = glCreateProgram();
}

Program::~Program()
{
  remove();
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

void Program::remove()
{
  if(!m_removed) {
    glDeleteProgram(m_id);
    m_removed = true;
    Log::debug("deleting opengl shader prgram");
  }
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
    Log::debug("create_glsl_program(...) failed to load vertex shader");
    return false;
  }
  vshader.create();

  Shader fshader(Shader::Type::FRAGMENT);
  result = fshader.load(fshader_file);
  if(!result)
  {
    Log::debug("create_glsl_program(...) failed to load fragment shader");
    return false;
  }
  fshader.create();

  program.attachShaders(vshader, fshader);

  return true;
}

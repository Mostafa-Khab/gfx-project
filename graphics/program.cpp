#include <glad/gl.h>
#include <debug.hpp>

#include <logger.hpp>


#include "program.hpp"

namespace gfx
{


program::program()
{
  m_id = glCreateProgram();
}

program::~program()
{
  remove();
}

void program::attachShaders(shader& vertex, shader& frag)
{
  glAttachShader(m_id, vertex.getID());
  glAttachShader(m_id, frag.getID());
}

void program::link()
{
  glLinkProgram(m_id);
}

void program::use()
{
  glUseProgram(m_id);
}

void program::remove()
{
  if(!m_removed) {
    glDeleteProgram(m_id);
    m_removed = true;
    Log::debug("deleting opengl shader prgram");
  }
}

//remember to call link after reloading
void program::reload(std::string vshader_file, std::string fshader_file)
{
  remove();
  m_id = glCreateProgram();
  if(!m_id)
    Log::error("failed to recreate program in  program::reload");

  create(vshader_file, fshader_file);

}

int program::getUniformLocation(const char* name)
{
  return glGetUniformLocation(m_id, name);
}

int program::getAttribLocation(const char* name)
{
  return glGetAttribLocation(m_id, name);
}

bool program::create(std::string vshader_file,std::string fshader_file)
{

  shader vshader(shader::Type::VERTEX);
  bool result = vshader.load(vshader_file);
  if(!result)
  {
    Log::debug("glsl program creation failed to load vertex shader");
    return false;
  }
  vshader.create();

  shader fshader(shader::Type::FRAGMENT);
  result = fshader.load(fshader_file);
  if(!result)
  {
    Log::debug("glsl program creation failed to load fragment shader");
    return false;
  }
  fshader.create();

  attachShaders(vshader, fshader);

  return true;
}

}

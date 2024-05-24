#include <glad/gl.h>

#include <fstream>
#include <sstream>

#include <debug.hpp>
#include "shader.hpp"

namespace gfx
{

  shader::shader(shader::Type type): m_type(type), m_deleted(false)
  {

  }

  shader::~shader()
  {
    remove();
  }

  bool shader::load(std::string path)
  {
    std::ifstream     file(path);
    std::string       line;
    std::stringstream ss;

    if(!file.is_open()) 
    {
       Log::debug("failed to open shader file");
       return false;
    }

    while(std::getline(file, line))
    {
      ss << line << '\n';
    }

    m_source = ss.str();
    return true;

  }

  void shader::remove()
  {
    if(!m_deleted)
    {
      m_deleted = true;
      glDeleteShader(m_id);
      Log::debug("marking shader for deletion");
    }
  }

  void shader::create()
  {
    if(m_type == Type::VERTEX)
    {
      m_id = glCreateShader(GL_VERTEX_SHADER);
    } else {
      m_id = glCreateShader(GL_FRAGMENT_SHADER);
    }
    const char* src = &(m_source[0]);

    glShaderSource(m_id, 1 ,&src, NULL);
    glCompileShader(m_id);
  }

  const unsigned int& shader::getID()
  {
    return m_id;
  }
}

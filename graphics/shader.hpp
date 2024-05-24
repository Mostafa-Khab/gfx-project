/************************* 
 *  author : mostafa khaled 
 *  date   : Tue Feb  6 09:52:20 PM EET 2024
 *  why    : simplify shader loading and dealing with it
*************************/ 

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

namespace gfx
{

  class shader 
  {
    public:
      enum Type { VERTEX, FRAGMENT, NONE };

    public:
      shader(Type t = NONE);
     ~shader();

      bool load(std::string file_path);
      void remove(); //delete but the name is used
      void create();
                     
      const unsigned int& getID();

    private:
      Type              m_type;
      unsigned int      m_id;
      std::string       m_source;
      bool              m_deleted;
  };

}
#endif

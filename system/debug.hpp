/************************* 
 *  author : mostafa khaled 
 *  date   : Tue Feb  6 07:38:26 PM EET 2024
 *  why    : for debugging openGL code 
*************************/ 

#include <logger.hpp>

//if x == false exit must be called within main() function
#define ASSERT(x, y) if((x) == false) { Log::info((y)); return -1;}
//same as assert but terminates glfw.
#define GLFW_ASSERT(x, y) if((x) == false) { glfwTerminate(); Log::info((y)); return -1;}

namespace test
{
  void print (std::string_view string); //print a certian message
  void dprint(std::string_view string); //print a certian message if DEBUG or _DEBUG

  char pause();
}

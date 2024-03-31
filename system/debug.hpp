/************************* 
 *  author : mostafa khaled 
 *  date   : Tue Feb  6 07:38:26 PM EET 2024
 *  why    : for debugging openGL code 
*************************/ 

#include <string>

namespace test
{
  void print (std::string_view string); //print a certian message
  void dprint(std::string_view string); //print a certian message if DEBUG or _DEBUG

  void assert (bool expr, std::string_view error_msg, int code = -1); //make sure expr is true. exit if it isn't.
  void dassert(bool expr, std::string_view error_msg, int code = -1); //make sure expr is true. exit if it isn't. DEBUG or _DEBUG

  void glfw_assert (bool expr, std::string_view error_msg, int code = -1);
  void dglfw_assert(bool expr, std::string_view error_msg, int code = -1);

  char pause();
}

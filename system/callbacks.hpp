/************************* 
 *  author : mostafa khaled 
 *  date   : Wed Feb  7 10:49:08 PM EET 2024
 *  why    : callbacks for glfw
*************************/ 
struct GLFWwindow;

namespace gfx
{

  namespace callback
  {
    void error(int error, const char* desc);
    void key(GLFWwindow* window, int key, int scancode, int action, int mods);
  }

}


/************************* 
 *  author : mostafa khaled 
 *  date   : Wed Feb  7 10:49:08 PM EET 2024
 *  why    : callbacks for glfw
*************************/ 
struct GLFWwindow;

namespace gfx
{
  template <typename T> struct vector2;

  //NOTE: to use this class. the z-difference between eye and target in gfx::view must be equal one
  //if the above not provided. weird position of mouse will appear in your game.
  class mouse
  {
    public:
      static void update(GLFWwindow* window);

    public:
      static double x;
      static double y;
      static int button;
      static bool pressed;
      
  };
  

  namespace callback
  {
    void error(int error, const char* desc);
    void key(GLFWwindow* window, int key, int scancode, int action, int mods);
    void button(GLFWwindow* window, int button, int action , int mods);
  }

}


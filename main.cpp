#include <glad/gl.h>

#include "system.hpp"
#include "graphics.hpp"

void handle_input(GLFWwindow* window, gfx::vector3f& eye, float dt, std::function<float(float)> ease);

bool pressed = false;

void key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(key == GLFW_KEY_J && action == GLFW_PRESS)
    ::pressed = true;
  else if(key == GLFW_KEY_J && action == GLFW_RELEASE)
    ::pressed = false;

  gfx::callback::key(window, key, scancode, action, mods);
}

int main(int argc, const char* argv[])
{
  const int width  = 700;
  const int height = 700;

  gfx::context context;
  context.setVersion({2, 0});
  context.setWindowData(width, height, "gfx-test");

  bool result = context.init();
  GLFW_ASSERT(result, "failed to create gfx context");

  GLFWwindow* window;
  context.getWindow(window);

  glfwSetKeyCallback(window, key);

  gfx::program program;
  program.create(
      "/home/sasa/shaders/shader3d.vert",
      "/home/sasa/shaders/shader3d.frag"
      );
  program.link();

  int mvp_loc                      = program.getUniformLocation("MVP");
  gfx::attributes::vpos_location() = program.getAttribLocation("vPos");
  gfx::attributes::vcol_location() = program.getAttribLocation("vCol");


  gfx::box box{-1.f, -1.f, 0.4, 0.4};
  gfx::vbuffer<gfx::vertex3d> vbuff;

  vbuff.bind();
    vbuff.append(box, gfx::vertex3d(0, 0, 1, gfx::hex(0xd65d0eff)), false);
  vbuff.load_data();

  gfx::clock timer;

  gfx::view view(width, height);
  float fov = 1.57;

  gfx::vector3f eye(0, 0, 2.25);
  gfx::vector3f centre(0, 0,  1);
  gfx::vector3f up(0, 1,  0);


  gfx::vector2f start (-1.f,-1.f);
  gfx::vector2f mid1  (-1.f, 1.f);
  gfx::vector2f mid1_2( 0.f, 0.f);
  gfx::vector2f mid2  ( 1.f, 1.f);
  gfx::vector2f end   ( 1.f,-1.f);

  gfx::task2d_queue  tasks;
  tasks.push(gfx::task2d(start, mid1, 1.5, gfx::cubic::ease_inout));
  tasks.push(gfx::task2d(mid1, mid1_2, 1.5, gfx::cubic::ease_inout));
  tasks.push(gfx::task2d(mid1_2, mid2, 1.5, gfx::cubic::ease_inout));
  tasks.push(gfx::task2d(mid2, end, 1.5, gfx::cubic::ease_inout));

  gfx::vector2f start_size(0.4, 0.4);
  gfx::vector2f end_size(0.3, 0.2);
  gfx::task2d_queue  box_tasks;
  box_tasks.push(gfx::task2d(start_size, end_size, 1.5, gfx::cubic::ease_inout));
  box_tasks.push(gfx::task2d(end_size, end_size, 3.f));
  box_tasks.push(gfx::task2d(end_size, start_size, 1.5, gfx::cubic::ease_inout));


  gfx::task_queue<gfx::task_rgba>   color_tasks;
  color_tasks.push(gfx::task_rgba(gfx::gruv::red, gfx::gruv::orange, 1.5, gfx::smoothstep));
  color_tasks.push(gfx::task_rgba(gfx::gruv::orange, gfx::gruv::orange, 3.f, gfx::smoothstep));
  color_tasks.push(gfx::task_rgba(gfx::gruv::orange, gfx::gruv::red, 1.5, gfx::smoothstep));

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
  glBlendEquation(GL_FUNC_ADD);

  while(!context.should_close())
  {
    float dt = timer.restart();

    view.update(window);
    view.data(eye, centre, up);
    view.perspective(fov, 0.f, 10.f);
    view.multiply();

    program.use();

    if(::pressed)
    {
      tasks.restart();
      box_tasks.restart();
      color_tasks.restart();
    }


    auto pos = tasks.play(dt); 
    auto size = box_tasks.play(dt);
    auto color                = color_tasks.play(dt);

    box.x = pos.x;
    box.y = pos.y;

    box.width  = size.x;
    box.height = size.y;

    for(int i = 0; i < vbuff.size(); ++i)
    {
      vbuff[i].r = color.r;
      vbuff[i].g = color.g;
      vbuff[i].b = color.b;
      vbuff[i].a = color.a;
    }

    vbuff.modify_box(box, 0, false);

    view.set_mvp(mvp_loc);

    handle_input(window, eye, dt, gfx::smoothstep);

    context.clear(gfx::gruv::white, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      vbuff.bind();
      vbuff.draw();
    context.display();

  }
  return 0;
}

void handle_input(GLFWwindow* window, gfx::vector3f& eye, float dt, std::function<float(float)> ease)
{
  float speed = 2.5; 
  static float t = 0.f;
  bool pressed = false;

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    eye.x -= ease(t) * speed * dt;
    pressed = true;
  }

  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    eye.x += ease(t) * speed * dt;
    pressed = true;
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    eye.z -= ease(t) * speed * dt;
    pressed = true;
  }

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    eye.z += ease(t) * speed * dt;
    pressed = true;
  }

  if(pressed)
    t += dt * 0.7;
  else
    t -= dt * 3;

  if(t < 0.f)
    t = 0.f;

  if(t > 1.f)
    t = 1.f;

}

#include <glad/gl.h>
#include <iostream>

#include "graphics.hpp"
#include "system.hpp"


void handleInput(GLFWwindow* window, gfx::vbuffer<gfx::vertex3d>& vertex_buffer, float dt, std::function<float(float)> func);

void lerp(gfx::vbuffer<gfx::vertex3d>& vbuff, const gfx::vector3f& centre, const gfx::vector3f& end, float size, float t)
{
  
  vbuff[0].x = gfx::lerp(centre.x + size, end.x + size, t);
  vbuff[0].y = gfx::lerp(centre.y - size, end.y - size, t);

  vbuff[1].x = gfx::lerp(centre.x - size, end.x - size, t);
  vbuff[1].y = gfx::lerp(centre.y - size, end.y - size, t);

  vbuff[2].x = gfx::lerp(centre.x + size, end.x + size, t);
  vbuff[2].y = gfx::lerp(centre.y + size, end.y + size, t);

  vbuff[3].x = gfx::lerp(centre.x - size, end.x - size, t);
  vbuff[3].y = gfx::lerp(centre.y + size, end.y + size, t);

  vbuff.modify();
}

int main()
{
  constexpr int width  = 700;
  constexpr int height = 700;

  gfx::context context;
  context.setVersion({ 2 , 0 });
  context.setWindowData(width, height, "gfx-test");

  //a window is created in here. you can get a pointer to that window
  bool result = context.init();
  GLFW_ASSERT(result, "failed to init gfx context");

  gfx::vector3f centre(-0.9f , -0.9f, -1.f);
  float size = 0.2f;

  auto color = gfx::hex(0xcc241dff);

  gfx::vertex3d_buf vertex_buffer;
  vertex_buffer.bind();
  vertex_buffer.append(gfx::vertex3d(centre.x + size, centre.y - size, centre.z, color));
  vertex_buffer.append(gfx::vertex3d(centre.x - size, centre.y - size, centre.z, color));
  vertex_buffer.append(gfx::vertex3d(centre.x + size, centre.y + size, centre.z, color));
  vertex_buffer.append(gfx::vertex3d(centre.x - size, centre.y + size, centre.z, color));
  
  vertex_buffer.load_data(GL_STATIC_DRAW);
  
  gfx::program prg;
  prg.create("/home/sasa/shaders/shader3d.vert", "/home/sasa/shaders/shader3d.frag");
  prg.link();

  int mvp_location  = prg.getUniformLocation("MVP");
  gfx::attributes::vpos_location() = prg.getAttribLocation("vPos");
  gfx::attributes::vcol_location() = prg.getAttribLocation("vCol");

  GLFWwindow* window;
  context.getWindow(window);

  auto tp = gfx::datetime(2006, 10, 5, 27, 20);
  std::cout << gfx::strtime(tp);
  
  glfwSetKeyCallback(window, gfx::callback::key);
  gfx::clock c, cf;
  int   frq;
  float dt;

  gfx::view vw(width, height);

  gfx::vector3f eye (0, 0, 2);
  gfx::vector3f lookat (0, 0, 1);
  gfx::vector3f up (0, 1, 0);

  vw.data(eye, lookat, up);

  float t = 0;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);

  const gfx::vector3f end ( 1.f, -1.f, -1.f);
  const gfx::vector3f mid1(-1.f , 2.f, -1.f);
  const gfx::vector3f mid2( 0.3 , 1.f, -1.f);


  while(!context.should_close())
  {
    dt = cf.restart();

    vw.update(window);
    vw.perspective();
    vw.multiply();

    handleInput(window, vertex_buffer, dt, gfx::smoothstep);

    if (t < 1.f)
    {

      float st = gfx::cubic::ease_inout(t);
      auto mid = gfx::lerp(mid1, mid2, st);
      lerp(vertex_buffer, gfx::lerp(centre, mid, st), gfx::lerp(mid, end, st), size, st);
    }

    t += dt * 0.3f;

    prg.use();
    vw.set_mvp(mvp_location);

    context.clear(gfx::gruv::white, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      vertex_buffer.draw(GL_TRIANGLE_STRIP);
    context.display();
    
    if(c.elapsed() > 1.f)
    {
      std::cout << "fps--> " << frq << '\n';
      frq = 0;
      c.restart();
    } else {
      ++frq;
    }

  }

  //contxt.terminate();
  return 0;
}

void handleInput(GLFWwindow* window, gfx::vbuffer<gfx::vertex3d>& vertex, float dt, std::function<float(float)> ease)
{
  bool updated = false;
  float speed = 2.5;
  static float t = 0.f;
  gfx::vector2f v(0.f, 0.f);

  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    v.x += speed;
    updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    v.x -= speed;
    updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    v.y += speed;
    updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    v.y -= speed;
    updated = true;
  }

  if(updated) {
    t += dt * 2;
  } else 
  {
    t -= dt * 5;
  }
    vertex.move(gfx::vector2f(ease(t) * dt * v.x, ease(t) * dt * v.y));
    vertex.modify();

  if(t > 1.f)
    t = 1.f;

  if(t < 0.f)
    t = 0.f;
}

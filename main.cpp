#include <glad/gl.h>
#include <iostream>
#include "graphics.hpp"
#include "system.hpp"

// if you run make install use (#include "GFX/graphics.hpp") instead
// if you run make install use (#include "GFX/system.hpp") instead

//void handleInput(GLFWwindow* window, gfx::vbuffer<gfx::vertex2d>& vertex_buffer, float dt);

float f(float x)
{
  x -= 1.5f;
  return x * x;
}

void print(gfx::vbuffer<gfx::vertex2d>& );

const gfx::vector2f end(1.f, 1.f);

//t is the step that depends on time!!
void lerp(gfx::vbuffer<gfx::vertex2d>& vbuff, gfx::vector2f& centre, float size, float t)
{
  if (t > 0.9)
    return;
  
  vbuff[0].x = gfx::lerp(centre.x + size, end.x + size, t);
  vbuff[0].y = gfx::lerp(centre.y - size, end.y - size, t);

  vbuff[1].x = gfx::lerp(centre.x - size, end.x - size, t);
  vbuff[1].y = gfx::lerp(centre.y - size, end.y - size, t);

  vbuff[2].x = gfx::lerp(centre.x + size, end.x + size, t);
  vbuff[2].y = gfx::lerp(centre.y + size, end.y + size, t);

  vbuff[3].x = gfx::lerp(centre.x - size, end.x - size, t);
  vbuff[3].y = gfx::lerp(centre.y + size, end.y + size, t);

  //print(vbuff);
  vbuff.modify();
}

void print(gfx::vbuffer<gfx::vertex2d>& vbuff)
{
  for(int i = 0; i < vbuff.size(); ++i)
  {
    std::cout << vbuff[i].x << ' ' << vbuff[i].y << '\n';
  }
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

  gfx::vector2f centre(-0.7f , -0.7f);
  float size = 0.2f;

  gfx::vertex2d_buf vertex_buffer;
  vertex_buffer.bind();
  vertex_buffer.append(gfx::vertex2d(centre.x + size, centre.y - size, 1.0, 0.4, 0.2));
  vertex_buffer.append(gfx::vertex2d(centre.x - size, centre.y - size, 1.0, 0.4, 0.2));
  vertex_buffer.append(gfx::vertex2d(centre.x + size, centre.y + size, 0.6, 0.4, 0.2));
  vertex_buffer.append(gfx::vertex2d(centre.x - size, centre.y + size, 0.6, 0.4, 0.2));
  
  vertex_buffer.load_data(GL_STATIC_DRAW);
  
  gfx::shader vertex_shader(gfx::shader::VERTEX);
  result = vertex_shader.load("../shaders/default.vert");
  if(!result)
  {
    glfwTerminate();
    return -1;
  }
  vertex_shader.create();

  gfx::shader fragment_shader(gfx::shader::FRAGMENT);
  result = fragment_shader.load("../shaders/default.frag");
  if(!result)
  {
    glfwTerminate();
    return -1;
  }
  fragment_shader.create();

  gfx::program prg;
  prg.attachShaders(vertex_shader, fragment_shader);
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

  float t = 0;
  while(!context.should_close())
  {
    dt = cf.restart();

    vw.update(window);
    vw.ortho();
    vw.multiply();

 //   handleInput(window, vertex_buffer, dt);
    lerp(vertex_buffer, centre, size, t);
    t += dt * 0.3f;

    prg.use();
    vw.set_mvp(mvp_location);

    context.clear(gfx::rgba(0.f,0.f,0.f,1.f), GL_COLOR_BUFFER_BIT);
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

void handleInput(GLFWwindow* window, gfx::vbuffer<gfx::vertex2d>& vertex, float dt)
{
  bool updated = false;
  float speed = 2.5;
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    for(int i = 0; i < 4; ++i)
    {
      vertex[i].x += speed * dt;      
    }
      updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    for(int i = 0; i < 4; ++i)
    {
      vertex[i].x -= speed * dt;      
    }
      updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    for(int i = 0; i < 4; ++i)
    {
      vertex[i].y += speed * dt;      
    }
      updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    for(int i = 0; i < 4; ++i)
    {
      vertex[i].y -= speed * dt;      
    }
      updated = true;
  }
  if(updated) { vertex.modify();}
}

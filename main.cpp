#include <glad/gl.h>
#include <iostream>
#include "graphics.hpp"
#include "system.hpp"
#include "linmath.h"

void handleInput(GLFWwindow* window, Buffer<Vertex>& vertex_buffer, float dt);

int main()
{
  const int width = 800;
  const int height = 600;
  Context context;
  context.setVersion({ 2 , 0 });
  context.setWindowData(800, 600, "my window");

  bool result = context.init(); //a window is created in here. you can get a pointer to that window
  test::glfw_assert(result, "failed to init context");

  Buffer<Vertex> vertex_buffer;
  Buffer<unsigned int> index_buffer;
  index_buffer.append(0);
  index_buffer.append(1);
  index_buffer.append(2);
  index_buffer.append(1);
  index_buffer.append(2);
  index_buffer.append(3);
  index_buffer.bind();
  index_buffer.load_data(GL_DYNAMIC_DRAW);

  vertex_buffer.bind();
  
  vertex_buffer.append(Vertex( 0.2, -0.2, 1.0, 0.4, 0.2));
  vertex_buffer.append(Vertex(-0.2, -0.2, 1.0, 0.4, 0.2));
  vertex_buffer.append(Vertex( 0.2,  0.2, 0.6, 0.4, 0.2));
  vertex_buffer.append(Vertex(-0.2,  0.2, 0.6, 0.4, 0.2));
  
  vertex_buffer.load_data(GL_STATIC_DRAW);
  
  Shader vertex_shader(Shader::VERTEX);
  test::glfw_assert(vertex_shader.load("../shaders/shader.vert"), "failed to load vertex shader");
  vertex_shader.create();

  Shader fragment_shader(Shader::FRAGMENT);
  test::glfw_assert(fragment_shader.load("../shaders/shader.frag"), "failed to load fragment shader");
  fragment_shader.create();

  Program program;
  program.attachShaders(vertex_shader, fragment_shader);
  program.link();

  int mvp_location  = program.getUniformLocation("MVP");
  Attributes::vpos_location() = program.getAttribLocation("vPos");
  Attributes::vcol_location() = program.getAttribLocation("vCol");

  Vertex::set_attributes();

  GLFWwindow* window;
  context.getWindow(window);

  auto tp = datetime(2006, 10, 5, 27, 20);
  std::cout << strtime(tp);
  
  glfwSetKeyCallback(window, callback::key);
  Clock c, cf;
  int   frq;
  float dt;

  View view(width, height);

  while(!context.should_close())
  {
    dt = cf.restart();

    view.update(window);
    mat4x4_identity(view.m());
    view.ortho();
    view.multiply();

    handleInput(window, vertex_buffer, dt);

    program.use();

    view.set_mvp(mvp_location);
    context.clear(0.15f, 0.3f, 0.3f, 1.f);
    index_buffer.draw(GL_TRIANGLES);
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

  //context.terminate();
  return 0;
}

void handleInput(GLFWwindow* window, Buffer<Vertex>& vertex, float dt)
{
  bool updated = false;
  float speed = 2.5;
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && vertex[0].x < 1.f)
  {
    for(int i = 0; i < 4; ++i)
    {
      vertex[i].x += speed * dt;      
    }
      updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && vertex[1].x > -1.f)
  {
    for(int i = 0; i < 4; ++i)
    {
      vertex[i].x -= speed * dt;      
    }
      updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && vertex[2].y < 1.f)
  {
    for(int i = 0; i < 4; ++i)
    {
      vertex[i].y += speed * dt;      
    }
      updated = true;
  }

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && vertex[0].y > -1.f)
  {
    for(int i = 0; i < 4; ++i)
    {
      vertex[i].y -= speed * dt;      
    }
      updated = true;
  }
  if(updated) { vertex.modify();}
}

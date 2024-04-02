#include <glad/gl.h>
#include <iostream>
#include "graphics.hpp"
#include "system.hpp"

void handleInput(GLFWwindow* window, Buffer<Vertex>& vertex_buffer, float dt);

int main()
{
  Context context;
  context.setVersion({ 2 , 0 });
  context.setWindowData(800, 600, "my window");

  bool result = context.init(); //a window is created in here. you can get a pointer to that window
  test::glfw_assert(result, "failed to init context");

  Buffer<unsigned int> index_buffer;
  index_buffer.append(0);
  index_buffer.append(1);
  index_buffer.append(2);
  index_buffer.append(1);
  index_buffer.append(2);
  index_buffer.append(3);

  index_buffer.bind();
  index_buffer.load_data(GL_DYNAMIC_DRAW);

  Buffer<Vertex> vertex_buffer;
  vertex_buffer.append(Vertex( 0.2, -0.2, 1.0, 0.4, 0.2));
  vertex_buffer.append(Vertex(-0.2, -0.2, 1.0, 0.4, 0.2));
  vertex_buffer.append(Vertex( 0.2,  0.2, 0.6, 0.4, 0.2));
  vertex_buffer.append(Vertex(-0.2,  0.2, 0.6, 0.4, 0.2));
  
  vertex_buffer.bind();
  vertex_buffer.load_data(GL_STATIC_DRAW);
  
  Program program;
  result = create_glsl_program(program, "../shaders/shader.vert", "../shaders/shader.frag");
  test::glfw_assert(result, "failed to create shader program");

  program.link();

  int mvp_location  = program.getUniformLocation("MVP");
  Attributes::vpos_location() = program.getAttribLocation("vPos");
  Attributes::vcol_location() = program.getAttribLocation("vCol");

  Vertex::set_attributes();

  GLFWwindow* window;
  context.getWindow(window);
  
  glfwSetKeyCallback(window, callback::key);
  glfwSetErrorCallback(callback::error);
  Clock c, cf;
  int   frq;
  float dt;

  View view(800, 600);

  while(!context.should_close())
  {
    dt = cf.restart();

    view.update(window);
    view.ortho(1, -1);
    view.multiply();

    handleInput(window, vertex_buffer, dt);

    program.use();

    view.set_mvp(mvp_location);

    context.clear(RGBA(0, 0, 0, 0));
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

  context.terminate();
  
  return 0;
}

void handleInput(GLFWwindow* window, Buffer<Vertex>& vertex, float dt)
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

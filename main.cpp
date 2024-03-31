#include <glad/gl.h>
#include <iostream>
#include "graphics.hpp"
#include "system.hpp"
#include "linmath.h"

#include <chrono>

class clock
{
  public:
    clock() = default;
   ~clock() = default;

   float elapsed();
   float restart();

  private:
    std::chrono::_V2::high_resolution_clock::time_point m_start;

};

float clock::elapsed()
{
  auto end = std::chrono::_V2::high_resolution_clock::now();
  std::chrono::duration<float> d = end - m_start;

  return d.count();
}

float clock::restart()
{
  auto end = std::chrono::_V2::high_resolution_clock::now();
  std::chrono::duration<float> d = end - m_start;
  m_start = end;

  return d.count();
}

void handleInput(GLFWwindow* window, Buffer<Vertex>& vertex_buffer, float dt);

int main()
{
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
  int vpos_location = program.getAttribLocation("vPos");
  int vcol_location = program.getAttribLocation("vCol");

  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));

  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 2));

  GLFWwindow* window;
  context.getWindow(window);

  auto tp = datetime(2006, 10, 5, 27, 20);
  std::cout << strtime(tp);
  
  glfwSetKeyCallback(window, callback::key);
  class clock c, cf;
  int   frq;
  float dt;

  while(!context.should_close())
  {
    dt = cf.restart();

    float ratio;
    int width, height;
    mat4x4 mvp, m, p;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;

    glViewport(0, 0, width, height);

    mat4x4_identity(m);
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    handleInput(window, vertex_buffer, dt);


    program.use();

    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const float*) mvp);
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

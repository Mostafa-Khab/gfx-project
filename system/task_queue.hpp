/*********************************
 * author     : mostafa khaled
 * date       : Sun Jun 23 10:24:25 PM EEST 2024
 * desc       : 
 ********************************/
#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP

#include <vector>

namespace gfx
{

  template <typename T>
  class task;

  template <typename T>
  class quad_bezier;

  template <typename T>
  class cubic_bezier;

  //a wrapper to std::vector that stores some animation tasks and play them in squence.
  template <typename T>
  class task_queue
  {
    public: 
      task_queue(float cooldown = 0.f);
      virtual ~task_queue() = default;

      void push(const T&);
      void push(T&&);

      void restart();
      bool done();
      bool empty();

      void set_cooldown(float t);

      T& front();

      T& operator[] (int index);

      typename T::position_type play(float dt);

    protected: 
      std::vector<T>           m_tasks;
      int                      m_current; //the index of the current task to play.
      float                    m_cooldown;
      float                    m_cool_progress;
      bool                     m_cooling;
  };

  typedef task_queue<task<vector2<float>>> task2d_queue;
  typedef task_queue<task<vector3<float>>> task3d_queue;
  typedef task_queue<task<rgb>>  task_rgb_queue;
  typedef task_queue<task<rgba>> task_rgba_queue;



  typedef task_queue<quad_bezier<vector2<float>>> quad_bezier2d_queue;
  typedef task_queue<quad_bezier<vector3<float>>> quad_bezier3d_queue;
  typedef task_queue<quad_bezier<rgb>>  quad_bezier_rgb_queue;
  typedef task_queue<quad_bezier<rgba>> quad_bezier_rgba_queue;



  typedef task_queue<cubic_bezier<vector2<float>>> cubic_bezier2d_queue;
  typedef task_queue<cubic_bezier<vector3<float>>> cubic_bezier3d_queue;
  typedef task_queue<cubic_bezier<rgb>>  cubic_bezier_rgb_queue;
  typedef task_queue<cubic_bezier<rgba>> cubic_bezier_rgba_queue;

}


#endif /* !TASK_QUEUE_HPP */

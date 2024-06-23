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

  //template <typename T>
  //class task;

  //template <typename T>
  //class quad_bezier;

  //template <typename T>
  //class cubic_bezier;

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


}


#endif /* !TASK_QUEUE_HPP */

#include "vectors.hpp"
#include "color.hpp"
#include "interpolators.hpp"
#include "task.hpp"

namespace gfx
{
  template <typename T>
  task<T>::task(T s, T e, float t, std::function<float(float)> func)
    : m_start(s), m_finish(e), m_time(t), m_remain(t), m_progress(0.f), m_ease(func), m_done(false)
  {

  }

  template <typename T>
  T task<T>::operator() (float dt)
  {
    m_remain -= dt;
    if(m_remain <= 0.f)
       m_done = true;

    if(m_done)
      return m_finish;

    m_progress += (1.f / m_time) * dt;

    return gfx::lerp(m_start, m_finish, m_ease(m_progress));

  }

  template <typename T>
  void task<T>::restart()
  {
    m_remain   = m_time;
    m_progress = 0.f;
    m_done     = false;
  }

  //task_queue

  template<typename T>
  task_queue<T>::task_queue()
    : m_current(0)
  {

  }

  template<typename T>
  void task_queue<T>::push(const T& t)
  {
    m_tasks.push_back(t);
  }

  template<typename T>
  void task_queue<T>::push(T&& t)
  {
    m_tasks.push_back(t);
  }

  template<typename T>
  T& task_queue<T>::front()
  {
    return m_tasks.front();
  }

  template<typename T>
  T& task_queue<T>::operator[] (int index)
  {
    return m_tasks[index];
  }

  template<typename T>
  bool task_queue<T>::done()
  {
    return m_tasks.back().m_done;
  }

  template<typename T>
  bool task_queue<T>::empty()
  {
    return m_tasks.empty();
  }

  template<typename T>
  void task_queue<T>::restart()
  {
    if(m_current == 0 && m_tasks.size() == 0)
      return;

    for(int i = 0; i <= m_current; ++i)
    {
      m_tasks[i].restart();
    }

    m_current = 0;
  }

  //make sure to push tasks to queue before calling play(dt)!!
  template<typename T>
  typename T::position_type task_queue<T>::play(float dt)
  {
    auto pos = m_tasks[m_current](dt);
    if(m_tasks[m_current].m_done && m_current < m_tasks.size() - 1)
      ++m_current;

    return pos;
  }

  //a task with extra middle vector
  template <typename T>
  mid_task<T>::mid_task(T s, T m, T e, float t, std::function<float(float)> func)
    :task<T>(s, e, t, func), m_mid(m)
  {
  }

  template <typename T>
  T mid_task<T>::operator() (float dt)
  {
    
    m_remain -= dt;
    if(m_remain <= 0.f)
      m_done = true;

    if(m_done)
      return m_finish;

    m_progress += (1.f / m_time) * dt;

    return gfx::lerp(
              gfx::lerp( m_start,  m_mid, m_ease( m_progress)),
              gfx::lerp( m_mid,  m_finish, m_ease( m_progress)),
              m_ease( m_progress)
            );
  }

  template class task<vector2<float>>;
  template class task<vector3<float>>;

  template class task<rgb>;
  template class task<rgba>;


  template class task_queue<task<vector2<float>>>;
  template class task_queue<task<vector3<float>>>;

  template class task_queue<task<rgb>>;
  template class task_queue<task<rgba>>;



  template class mid_task<vector2<float>>;
  template class mid_task<vector3<float>>;

  template class mid_task<rgb>;
  template class mid_task<rgba>;

  template class task_queue<mid_task<vector2<float>>>;
  template class task_queue<mid_task<vector3<float>>>;

  template class task_queue<mid_task<rgb>>;
  template class task_queue<mid_task<rgba>>;
}

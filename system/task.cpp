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
  task_queue<T>::task_queue(float cooldown)
    : m_current(0), m_cooldown(cooldown), m_cool_progress(0), m_cooling(false)
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
  void task_queue<T>::set_cooldown(float t)
  {
    m_cooldown = t;
  }

  template<typename T>
  void task_queue<T>::restart()
  {
    if(m_current == 0 && m_tasks.size() == 0)
      return;

    if(m_cooling)
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
    if(m_tasks[m_current].m_done && m_current < m_tasks.size())
    {
      if(!m_cooling)
        m_cooling = true;

      m_cool_progress += dt;

      if(m_cool_progress >= m_cooldown)
      {
        if(++m_current >= m_tasks.size())
          m_current = m_tasks.size() - 1;


        m_cool_progress = 0.f;
        m_cooling = false;
      }
    }

    return pos;
  }

  //a task with extra middle vector
  template <typename T>
  quad_bezier<T>::quad_bezier(T s, T m, T e, float t, std::function<float(float)> func)
    :task<T>(s, e, t, func), m_mid(m)
  {
  }

  template <typename T>
  T quad_bezier<T>::operator() (float dt)
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

  //cubic bezier curve with 2 points between start and end
  template <typename T>
  cubic_bezier<T>::cubic_bezier(T p0, T p1, T p2, T p3, float t, std::function<float(float)> ease)
    : task<T>(p0, p3, t, ease), m_mid1(p1), m_mid2(p2)
  {

  }

  template <typename T>
  T cubic_bezier<T>::operator() (float dt)
  {
    
    m_remain -= dt;
    if(m_remain <= 0.f)
      m_done = true;

    if(m_done)
      return m_finish;

    m_progress += (1.f / m_time) * dt;

    auto r1 = gfx::lerp(m_start, m_mid1, m_ease(m_progress));
    auto r2 = gfx::lerp(m_mid1, m_mid2, m_ease(m_progress));
    auto r3 = gfx::lerp(m_mid2, m_finish, m_ease(m_progress));

    return gfx::lerp(
              gfx::lerp( r1,  r2, m_ease( m_progress)),
              gfx::lerp( r2,  r3, m_ease( m_progress)),
              m_ease( m_progress)
            );
  }
  /******************************************************/

  template class task<vector2<float>>;
  template class task<vector3<float>>;
  template class task<rgb>;
  template class task<rgba>;

  template class task_queue<task<vector2<float>>>;
  template class task_queue<task<vector3<float>>>;
  template class task_queue<task<rgb>>;
  template class task_queue<task<rgba>>;

  /******************************************************/

  template class quad_bezier<vector2<float>>;
  template class quad_bezier<vector3<float>>;
  template class quad_bezier<rgb>;
  template class quad_bezier<rgba>;

  template class task_queue<quad_bezier<vector2<float>>>;
  template class task_queue<quad_bezier<vector3<float>>>;
  template class task_queue<quad_bezier<rgb>>;
  template class task_queue<quad_bezier<rgba>>;

  /******************************************************/

  template class cubic_bezier<vector2<float>>;
  template class cubic_bezier<vector3<float>>;
  template class cubic_bezier<rgb>;
  template class cubic_bezier<rgba>;

  template class task_queue<cubic_bezier<vector2<float>>>;
  template class task_queue<cubic_bezier<vector3<float>>>;
  template class task_queue<cubic_bezier<rgb>>;
  template class task_queue<cubic_bezier<rgba>>;
}

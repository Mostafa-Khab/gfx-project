#include "task_queue.hpp"

namespace gfx
{ template<typename T>
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
    #ifdef DEBUG
      if(m_tasks.empty())
         Log::error("tried to access empty task_queue");
    #endif
    return m_tasks.front();
  }

  template<typename T>
  T& task_queue<T>::operator[] (int index)
  {
    #ifdef DEBUG
      if(m_tasks.empty() || index > m_tasks.size())
         Log::error("tried to access invalid task_queue index, or it is empty");
    #endif

    return m_tasks[index];
  }

  template<typename T>
  bool task_queue<T>::done()
  {
    #ifdef DEBUG
      if(m_tasks.empty())
         Log::error("tried to access empty task_queue done bool member");
    #endif
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

  
}

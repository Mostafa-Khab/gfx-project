#include "vectors.hpp"
#include "color.hpp"
#include "interpolators.hpp"

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


  /******************************************************/

  template class quad_bezier<vector2<float>>;
  template class quad_bezier<vector3<float>>;
  template class quad_bezier<rgb>;
  template class quad_bezier<rgba>;


  /******************************************************/

  template class cubic_bezier<vector2<float>>;
  template class cubic_bezier<vector3<float>>;
  template class cubic_bezier<rgb>;
  template class cubic_bezier<rgba>;

}

/*********************************
 * author     : mostafa khaled
 * date       : Wed May 29 01:51:19 PM EEST 2024
 * desc       : 
 ********************************/
#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <vector>

namespace gfx
{
  template <typename T>
  struct vector2;

  template <typename T>
  struct vector3;

  struct rgb;
  struct rgba;

  float smoothstep(float t);

  //animation task
  //to accept both vector2 and vector3
  //a lerp version that accepts T (position_type or even colors) must exist.
  template <typename T>
  class task 
  {
    public:
      typedef T position_type;
    public:
      task(
             T start,
             T end, 
             float total_time, 
             std::function<float(float)> ease = smoothstep
          );
      virtual ~task() = default;

      void restart();

      virtual T operator() (float dt);

    protected:
      T                           m_start;
      T                           m_finish;
      float                       m_time; //total time taken by the animation task.o
      float                       m_remain;
      float                       m_progress;
      std::function<float(float)> m_ease;
      
    public:
      bool                        m_done;

  };

  typedef task<vector2<float>> task2d;
  typedef task<vector3<float>> task3d;
  typedef task<rgb> task_rgb;
  typedef task<rgba> task_rgba;

  //a task class that have extra mid point to be lerped in operator() or play in queue
  //this class can be named quad_bezier_task
  template <typename T>
  class quad_bezier : public task<T>
  {
    public:
      typedef T position_type; 
    public:
      //start, middle, end vectors
      //^      ^       ^
      quad_bezier(T s, T m, T e, float t, std::function<float(float)> func = smoothstep);

      position_type operator() (float dt) override;

      ~quad_bezier() = default;


    protected:
      using task<T>::m_start;
      using task<T>::m_finish;
      using task<T>::m_time; //total time taken by the animation task.o
      using task<T>::m_remain;
      using task<T>::m_progress;
      using task<T>::m_ease;

      position_type     m_mid;

    public:
      using task<T>::m_done;
  };

  typedef quad_bezier<vector2<float>> quad_bezier2d;
  typedef quad_bezier<vector3<float>> quad_bezier3d;
  typedef quad_bezier<rgb>  quad_bezier_rgb;
  typedef quad_bezier<rgba> quad_bezier_rgba;


  template <typename T>
  class cubic_bezier : public task<T>
  {
    public:
      typedef T position_type; 
    public:
      //start, middle, end vectors
      //^      ^       ^
      cubic_bezier(T p0, T p1, T p2, T p3, float t, std::function<float(float)> func = smoothstep);

      position_type operator() (float dt) override;

      ~cubic_bezier() = default;


    protected:
      using task<T>::m_start;
      using task<T>::m_finish;
      using task<T>::m_time; //total time taken by the animation task.o
      using task<T>::m_remain;
      using task<T>::m_progress;
      using task<T>::m_ease;

      position_type     m_mid1, m_mid2;

    public:
      using task<T>::m_done;
  };

  typedef cubic_bezier<vector2<float>> cubic_bezier2d;
  typedef cubic_bezier<vector3<float>> cubic_bezier3d;
  typedef cubic_bezier<rgb>  cubic_bezier_rgb;
  typedef cubic_bezier<rgba> cubic_bezier_rgba;

}


#endif /* !TASK_HPP */

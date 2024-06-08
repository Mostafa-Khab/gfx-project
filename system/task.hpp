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

  typedef task_queue<quad_bezier<vector2<float>>> quad_bezier2d_queue;
  typedef task_queue<quad_bezier<vector3<float>>> quad_bezier3d_queue;
  typedef task_queue<quad_bezier<rgb>>  quad_bezier_rgb_queue;
  typedef task_queue<quad_bezier<rgba>> quad_bezier_rgba_queue;

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

  typedef task_queue<cubic_bezier<vector2<float>>> cubic_bezier2d_queue;
  typedef task_queue<cubic_bezier<vector3<float>>> cubic_bezier3d_queue;
  typedef task_queue<cubic_bezier<rgb>>  cubic_bezier_rgb_queue;
  typedef task_queue<cubic_bezier<rgba>> cubic_bezier_rgba_queue;
}


#endif /* !TASK_HPP */

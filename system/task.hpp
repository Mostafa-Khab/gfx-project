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
      task_queue();
      virtual ~task_queue() = default;

      void push(const T&);
      void push(T&&);

      void restart();
      bool done();
      bool empty();

      T& front();

      T& operator[] (int index);

      typename T::position_type play(float dt);

    protected: 
      std::vector<T>           m_tasks;
      int                      m_current; //the index of the current task to play.
  };

  typedef task_queue<task<vector2<float>>> task2d_queue;
  typedef task_queue<task<vector3<float>>> task3d_queue;
  
  typedef task_queue<task<rgb>>  task_rgb_queue;
  typedef task_queue<task<rgba>> task_rgba_queue;

  //a task class that have extra mid point to be lerped in operator() or play in queue
  template <typename T>
  class mid_task : public task<T>
  {
    public:
      typedef T position_type; 
    public:
      //start, middle, end vectors
      //^      ^       ^
      mid_task(T s, T m, T e, float t, std::function<float(float)> func = smoothstep);

      position_type operator() (float dt) override;

      ~mid_task() = default;


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

  typedef mid_task<vector2<float>> mid_task2d;
  typedef mid_task<vector3<float>> mid_task3d;

  typedef mid_task<rgb>  mid_task_rgb;
  typedef mid_task<rgba> mid_task_rgba;

  typedef task_queue<mid_task<vector2<float>>> mid_task2d_queue;
  typedef task_queue<mid_task<vector3<float>>> mid_task3d_queue;

  typedef task_queue<mid_task<rgb>>  mid_task_rgb_queue;
  typedef task_queue<mid_task<rgba>> mid_task_rgba_queue;
}


#endif /* !TASK_HPP */

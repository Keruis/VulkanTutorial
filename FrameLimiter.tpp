/*
 * File:    FrameLimiter.tpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Renderer
 * Brief:   FrameLimiter 类内联函数的实现（模板实现文件）。
 *
 * Description:
 *   This file contains the inline member function implementations for the
 *   FrameLimiter class, including methods like beginFrame(), endFrame(),
 *   SetFPS(), and delta time calculation.
 *
 *   本文件实现了 FrameLimiter 类的成员函数定义，包括每帧起止控制、
 *   帧率设置、deltaTime 计算等，适用于头文件中声明的内联函数或模板函数。
 *   为确保模板或 inline 函数在编译期可见，通常在头文件中直接 include。
 *
 * Note:
 *   - This file is included at the end of FrameLimiter.h.
 *   - Not a standalone compilation unit.
 *
 * License: MIT License
 */

#include "FrameLimiter.h"

inline 
    Render::utils::FrameLimiter::FrameLimiter
(double target_fps, double sleep_precision_sec)
    : frame_duration(1.0 / target_fps),
      sleep_precision(sleep_precision_sec),
      last_frame_time(clock::now())
{

}


inline void 
    Render::utils::FrameLimiter::beginFrame
() 
    noexcept 
{
    auto now = clock::now();
    delta_time = std::chrono::duration<double>(now - last_frame_time).count();
    current_frame_time = now;
}


inline void 
    Render::utils::FrameLimiter::endFrame
() 
    noexcept 
{
    last_frame_time = current_frame_time;

    auto now = clock::now();
    duration elapsed = now - current_frame_time;
    double time_left = frame_duration - elapsed.count();

    if (time_left > sleep_precision) {
        std::this_thread::sleep_for(duration(time_left - sleep_precision));
    }

    while ((clock::now() - current_frame_time).count() < frame_duration) {

    }
}


inline void 
    Render::utils::FrameLimiter::SetFPS
(double fps) 
    noexcept 
{
    frame_duration = 1.0 / fps;
}


inline double 
    Render::utils::FrameLimiter::GetFPS
() 
    const noexcept 
{
    return 1.0 / frame_duration;
}


inline double 
    Render::utils::FrameLimiter::GetDeltaTime
() 
    const noexcept 
{
    return delta_time;
}
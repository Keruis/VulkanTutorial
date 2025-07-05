/*
 * File:    FrameLimiter.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Renderer
 * Brief:   提供帧率限制功能，用于保持稳定渲染帧率与帧间时间。
 *
 * Description:
 *   This header defines the FrameLimiter class, a utility for capping the
 *   frame rate in real-time rendering systems. It calculates the frame delta
 *   time and sleeps the thread to maintain the target FPS.
 *
 *   FrameLimiter 类用于限制每秒渲染帧数，通过计算帧间隔时间并主动休眠，
 *   保持渲染帧率稳定，避免 CPU 资源过度占用。常用于游戏循环或实时图形系统。
 *
 * Usage:
 *     FrameLimiter limiter(60.0); // Target 60 FPS
 *     limiter.beginFrame();
 *     // ... rendering ...
 *     limiter.endFrame();
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_FRAMELIMITER_H
#define BLUEPRINT_FRAMELIMITER_H

#include <chrono>
#include <thread>
#include "Attribute.h"

namespace Render::utils {
    class FrameLimiter {
    public:
        using clock     =   std::chrono::steady_clock;
        using duration  =   std::chrono::duration<double>;

        explicit                FrameLimiter            (double target_fps = 60.0, double sleep_precision_sec = 0.001);

        ALWAYS_INLINE void      beginFrame              ()                                                                  noexcept;
        ALWAYS_INLINE void      endFrame                ()                                                                  noexcept;

        ALWAYS_INLINE void      SetFPS                  (double fps)                                                        noexcept;
        ALWAYS_INLINE double    GetFPS                  () const                                                            noexcept;
        ALWAYS_INLINE double    GetDeltaTime            () const                                                            noexcept;

    private:
        double              frame_duration;
        double              sleep_precision;
        clock::time_point   current_frame_time;
        double              delta_time              = 0.0f;
        clock::time_point   last_frame_time;
    };
}

#include "FrameLimiter.tpp"

#endif //BLUEPRINT_FRAMELIMITER_H

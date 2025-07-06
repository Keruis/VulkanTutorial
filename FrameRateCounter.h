/*
 * File:    FrameRateCounter.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Renderer
 * Brief:   异步帧率统计器模板类，支持平均与 EMA 平滑模式。
 *
 * Description:
 *   This header defines the AsyncFrameRateCounter class template, which records
 *   frame timestamps in real-time and computes FPS statistics (instantaneous,
 *   min, max, average) in a background thread.
 *
 *   支持两种平滑模式：
 *     - SmoothingMode::Average：固定窗口平均；
 *     - SmoothingMode::EMA     ：指数加权移动平均（Exponential Moving Average）。
 *
 *   用户可调用 notify_frame() 通知新的一帧，统计过程在后台线程异步执行，
 *   可通过 GetFPS() 获取当前帧率，也可使用 GetStats() 获取完整统计信息。
 *
 * Usage:
 *     AsyncFrameRateCounter<SmoothingMode::EMA> counter;
 *     counter.notify_frame();
 *     float fps = counter.GetFPS();
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_FRAMERATECOUNTER_H
#define BLUEPRINT_FRAMERATECOUNTER_H

#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>
#include <deque>
#include <utility>
#include <numeric>
#include <condition_variable>

#include "utils/constexprSwitch.h"

namespace Render::utils {
    enum class SmoothingMode {
        Average,
        EMA
    };

    struct FrameStats {
        float   fps;
        float   min_fps;
        float   max_fps;
        float   avg_fps;
    };

    template<SmoothingMode Mode = SmoothingMode::Average>
    class AsyncFrameRateCounter {
    public:
        using clock         =   std::chrono::steady_clock;
        using time_point    =   clock::time_point;

        explicit AsyncFrameRateCounter      (std::size_t max_samples = 100);
        ~AsyncFrameRateCounter              ();

        void        notify_frame            ();

        float       GetFPS                  ()      const;
        FrameStats  GetStats                ()      const;

    private:
        std::size_t             max_samples;
        std::deque<time_point>  frame_times;
        std::thread             worker;
        std::atomic<bool>       running;
        std::atomic<float>      fps_value;
        std::atomic<float>      min_fps;
        std::atomic<float>      max_fps;
        std::atomic<float>      avg_fps;

        mutable std::mutex      mtx;
        std::condition_variable cv;

        void         loop                   ();
    };
}

#include "FrameRateCounter.tpp"

#endif //BLUEPRINT_FRAMERATECOUNTER_H

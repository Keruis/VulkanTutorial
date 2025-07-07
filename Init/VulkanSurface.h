/*
 * File:    VulkanSurface.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   Vulkan 表面封装，用于与平台窗口系统（X11）集成。
 *
 * Description:
 *   This header defines the VulkanSurface class, which handles the creation
 *   and destruction of a Vulkan surface (VkSurfaceKHR) for rendering. It acts
 *   as the bridge between the Vulkan renderer and the underlying windowing
 *   system (Xlib in this case).
 *
 *   VulkanSurface 是连接 Vulkan 与平台窗口系统（如 X11）的关键组件。
 *   它创建 VkSurfaceKHR 以支持图像交换链的渲染目标初始化。
 *
 * Responsibilities:
 *   - createSurface(): 基于 X11 显示和窗口创建 Vulkan 表面。
 *   - DestroySurfaceKHR(): 销毁创建的 Vulkan 表面资源。
 *   - GetSurfaceKHR(): 提供访问内部 surface 的接口。
 *
 * Platform: X11 (Linux)
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANSURFACE_H
#define BLUEPRINT_VULKANSURFACE_H

#include <iostream>
#include <stdexcept>

#include <X11/Xlib.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>

#include "utils/KDebug.h"

namespace Vulkan::Init {
    class VulkanSurface {
    public:
        VulkanSurface();

        void            Initialize          ()                                                                  noexcept;

        void            createSurface       (VkInstance instance, Display* vulkanDisplay, Window vulkanWindow)          ;
        void            DestroySurfaceKHR   (VkInstance instance)                                               noexcept;

        VkSurfaceKHR    GetSurfaceKHR       ()                                                                  noexcept;
    private:
        VkSurfaceKHR m_surface;
    };
}

#endif //BLUEPRINT_VULKANSURFACE_H

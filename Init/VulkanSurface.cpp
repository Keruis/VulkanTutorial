/*
 * File:    VulkanSurface.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   实现 Vulkan 表面（VkSurfaceKHR）与 X11 窗口系统的创建与销毁。
 *
 * Description:
 *   This file implements the VulkanSurface class, responsible for creating
 *   a platform-specific Vulkan surface (VkSurfaceKHR) using the X11 windowing
 *   system. This surface is used for presentation via the Vulkan swapchain.
 *
 *   VulkanSurface.cpp 实现了跨平台图形接口 Vulkan 与 Linux 下 X11 窗口系统的集成，
 *   封装了 surface 创建、释放等与平台绑定的底层细节。
 *
 * Key Methods:
 *   - createSurface(): 使用 Xlib 创建 Vulkan surface。
 *   - DestroySurfaceKHR(): 清理 surface 资源，防止内存泄露。
 *   - GetSurfaceKHR(): 返回内部 VkSurfaceKHR。
 *
 * Note:
 *   - 当前仅实现 X11，未来可拓展支持 Wayland 或 Windows。
 *
 * License: MIT License
 */

#include "VulkanSurface.h"

Vulkan::Init::VulkanSurface::VulkanSurface
        ()
{

}

void
Vulkan::Init::VulkanSurface::Initialize
        ()
noexcept
{

}


void
Vulkan::Init::VulkanSurface::createSurface
        (VkInstance instance, Display *vulkanDisplay, Window vulkanWindow)
{
    VkXlibSurfaceCreateInfoKHR surfaceInfo{};
    surfaceInfo         .sType          =       VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    surfaceInfo         .dpy            =       vulkanDisplay;
    surfaceInfo         .window         =       vulkanWindow;

    VkResult            result          =       vkCreateXlibSurfaceKHR(instance, &surfaceInfo, nullptr, &m_surface);
    if (result != VK_SUCCESS) {
        std::cerr << "[FATAL] Failed to create Xlib surface! VkResult = " << result << std::endl;
        throw std::runtime_error("vkCreateXlibSurfaceKHR failed");
    }
}

void
Vulkan::Init::VulkanSurface::DestroySurfaceKHR
        (VkInstance instance)
noexcept
{
    vkDestroySurfaceKHR(instance, m_surface, nullptr);
}

VkSurfaceKHR
Vulkan::Init::VulkanSurface::GetSurfaceKHR
        ()
noexcept
{
    return m_surface;
}
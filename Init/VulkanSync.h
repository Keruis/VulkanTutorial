/*
 * File:    VulkanSync.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   Vulkan 同步对象封装类，管理信号量和栅栏。
 *
 * Description:
 *   This header defines the VulkanSync class, which encapsulates the creation
 *   and management of Vulkan synchronization primitives, including semaphores
 *   and fences for per-frame rendering synchronization.
 *
 *   本类用于管理 Vulkan 同步机制中的核心资源：
 *     - 图像获取信号量（imageAvailableSemaphore）
 *     - 渲染完成信号量（renderFinishedSemaphore）
 *     - 每帧栅栏（inFlightFence）
 *   它是帧调度中的必要组件，确保图像正确、有序地提交与展示。
 *
 * Responsibilities:
 *   - createSyncObjects(): 创建一帧中所需的全部同步对象。
 *   - GetImageAvailableSemaphore(): 获取图像可用信号量引用。
 *   - GetRenderFinishedSemaphore(): 获取渲染完成信号量引用。
 *   - GetFlightFence(): 获取帧栅栏引用。
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANSYNC_H
#define BLUEPRINT_VULKANSYNC_H

#include <vector>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include "config.h"

namespace Vulkan::Init {
    class VulkanSync {
    public:
        VulkanSync();

        void Initialize() noexcept;

        void createSyncObjects(VkDevice device);

        std::vector<VkSemaphore>&   GetImageAvailableSemaphore() noexcept;
        std::vector<VkSemaphore>&   GetRenderFinishedSemaphore() noexcept;
        [[nodiscard]] const std::vector<VkSemaphore>&   GetImageAvailableSemaphore() const noexcept;
        [[nodiscard]] const std::vector<VkSemaphore>&   GetRenderFinishedSemaphore() const noexcept;
        std::vector<VkFence>&                       GetFlightFence() noexcept;
        [[nodiscard]] const std::vector<VkFence>&   GetFlightFence() const noexcept;

    private:
        std::vector<VkSemaphore>    imageAvailableSemaphore;
        std::vector<VkSemaphore>    renderFinishedSemaphore;
        std::vector<VkFence>        inFlightFence;
    };
}

#endif //BLUEPRINT_VULKANSYNC_H

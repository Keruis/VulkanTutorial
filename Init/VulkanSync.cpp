/*
 * File:    VulkanSync.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   实现 Vulkan 同步对象的创建和管理逻辑。
 *
 * Description:
 *   This source file implements the VulkanSync class, which manages Vulkan
 *   synchronization primitives used in multi-frame rendering:
 *     - VkSemaphore for image availability and render completion.
 *     - VkFence to track GPU execution status per frame.
 *
 *   These primitives are critical for frame lifecycle management,
 *   ensuring that CPU-GPU operations occur in a well-defined order.
 *
 *   本类是帧同步的基础组件，避免多帧资源冲突，
 *   并为帧间异步处理（如三重缓冲）提供支持。
 *
 * Related Methods:
 *   - createSyncObjects(): 创建 N 帧用的信号量和栅栏。
 *   - GetImageAvailableSemaphore(): 获取图像获取信号量。
 *   - GetRenderFinishedSemaphore(): 获取渲染完成信号量。
 *   - GetFlightFence(): 获取 GPU 执行状态的栅栏。
 *
 * License: MIT License
 */

#include "VulkanSync.h"

Vulkan::Init::VulkanSync::VulkanSync
() 
{

}


void 
    Vulkan::Init::VulkanSync::Initialize
() 
    noexcept 
{

}


void 
    Vulkan::Init::VulkanSync::createSyncObjects
(VkDevice device) 
{
    imageAvailableSemaphore     .resize (MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphore     .resize (MAX_FRAMES_IN_FLIGHT);
    inFlightFence               .resize (MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo   .sType      =       VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo       .sType      =       VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo       .flags      =       VK_FENCE_CREATE_SIGNALED_BIT;

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore[i]) != VK_SUCCESS ||
            vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

std::vector<VkSemaphore>& Vulkan::Init::VulkanSync::GetImageAvailableSemaphore() noexcept {
    return imageAvailableSemaphore;
}

std::vector<VkSemaphore>& Vulkan::Init::VulkanSync::GetRenderFinishedSemaphore() noexcept {
    return renderFinishedSemaphore;
}

const std::vector<VkSemaphore>& Vulkan::Init::VulkanSync::GetImageAvailableSemaphore() const noexcept {
    return imageAvailableSemaphore;
}

const std::vector<VkSemaphore>& Vulkan::Init::VulkanSync::GetRenderFinishedSemaphore() const noexcept {
    return renderFinishedSemaphore;
}

std::vector<VkFence>& Vulkan::Init::VulkanSync::GetFlightFence() noexcept {
    return inFlightFence;
}

const std::vector<VkFence>& Vulkan::Init::VulkanSync::GetFlightFence() const noexcept {
    return inFlightFence;
}
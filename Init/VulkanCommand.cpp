/*
 * File:    VulkanCommand.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   VulkanCommand 类的实现，负责创建命令池和主命令缓冲区。
 *
 * Description:
 *   This file implements the VulkanCommand class declared in VulkanCommand.h.
 *   It encapsulates the following Vulkan command infrastructure:
 *
 *     - Command pool creation using the graphics queue family index
 *     - Allocation of primary command buffers (one per frame in flight)
 *     - Provides accessors to the command pool and buffer list
 *
 *   在 Vulkan 渲染流程中，所有操作都需录制到命令缓冲中。
 *   本类实现了初始化命令池、分配命令缓冲区（可用于每帧绘制）的完整逻辑。
 *
 * Implementation Details:
 *   - Uses VkCommandPoolCreateInfo for pool creation
 *   - Uses VkCommandBufferAllocateInfo to allocate multiple buffers
 *   - 支持对多个 command buffer 的集中访问与生命周期管理
 *
 * License: MIT License
 */

#include "VulkanCommand.h"

Vulkan::Init::VulkanCommand::VulkanCommand
()
{

}


void
    Vulkan::Init::VulkanCommand::Initialize
()
    noexcept
{

}


void
    Vulkan::Init::VulkanCommand::createCommandPool
(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr)
{
    Vulkan::Init::QueueFamilyIndices queueFamilyIndices = Vulkan::Init::Utils::findQueueFamilies(physicalDevice, surfaceKhr);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo        .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo        .flags              = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo        .queueFamilyIndex   = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}


void
    Vulkan::Init::VulkanCommand::createCommandBuffer
(VkDevice device)
{
    m_commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo       .sType                  =       VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo       .commandPool            =       commandPool;
    allocInfo       .level                  =       VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo       .commandBufferCount     =       MAX_FRAMES_IN_FLIGHT;

    if (vkAllocateCommandBuffers(device, &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

VkCommandPool Vulkan::Init::VulkanCommand::GetCommandPool() noexcept {
    return commandPool;
}

std::vector<VkCommandBuffer>& Vulkan::Init::VulkanCommand::GetCommandBuffer() noexcept {
    return m_commandBuffers;
}

const std::vector<VkCommandBuffer>& Vulkan::Init::VulkanCommand::GetCommandBuffer() const noexcept {
    return m_commandBuffers;
}
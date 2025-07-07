/*
 * File:    VulkanCommand.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   封装 Vulkan 命令池（VkCommandPool）与命令缓冲区（VkCommandBuffer）管理逻辑。
 *
 * Description:
 *   This header defines the VulkanCommand class, which encapsulates the creation
 *   and management of the command pool and primary command buffers.
 *
 *   在 Vulkan 渲染管线中，所有的 GPU 操作都通过命令缓冲下达。
 *   本类用于初始化命令池（Command Pool）与帧缓冲数对应的主命令缓冲区：
 *
 *     - createCommandPool(): 为图形队列族创建命令池
 *     - createCommandBuffer(): 创建多个帧命令缓冲（用于绘制）
 *     - GetCommandPool(): 返回命令池句柄
 *     - GetCommandBuffer(): 访问当前所有命令缓冲
 *
 * Usage:
 *   VulkanCommand command;
 *   command.createCommandPool(...);
 *   command.createCommandBuffer(...);
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANCOMMAND_H
#define BLUEPRINT_VULKANCOMMAND_H

#include <stdexcept>

#include <vulkan/vulkan.h>

#include "config.h"
#include "VulkanFuncUtils.h"

namespace Vulkan::Init {
    class VulkanCommand {
    public:
        VulkanCommand();

        void            Initialize              ()                                                                          noexcept;

        void            createCommandPool       (VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr)         ;
        void            createCommandBuffer     (VkDevice device)                                                                   ;

        VkCommandPool   GetCommandPool          ()                                                                          noexcept;
        std::vector<VkCommandBuffer>&           GetCommandBuffer            ()                                              noexcept;
        [[nodiscard]] const std::vector<VkCommandBuffer>& GetCommandBuffer  ()                                        const noexcept;

    private:
        std::vector<VkCommandBuffer>    m_commandBuffers;
        VkCommandPool                   commandPool;
    };
}

#endif //BLUEPRINT_VULKANCOMMAND_H

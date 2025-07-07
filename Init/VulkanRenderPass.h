/*
 * File:    VulkanRenderPass.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   封装 Vulkan 渲染通道（VkRenderPass）的创建与管理。
 *
 * Description:
 *   This header defines the VulkanRenderPass class, which encapsulates
 *   the creation of a basic Vulkan render pass. The render pass describes
 *   how framebuffers are used during rendering, including attachments,
 *   subpasses, and dependencies.
 *
 *   渲染通道（Render Pass）定义了图像的读取、写入方式，是 Vulkan 渲染流程的核心组成部分。
 *   本类封装了以下操作：
 *
 *     - createRenderPass(): 创建单一子通道的标准 RenderPass
 *       用于清除颜色附件、写入交换链图像。
 *     - GetRenderPass(): 返回渲染通道句柄
 *
 * Typical usage:
 *   VulkanRenderPass pass;
 *   pass.createRenderPass(device, swapchain_format);
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANRENDERPASS_H
#define BLUEPRINT_VULKANRENDERPASS_H

#include <stdexcept>

#include <vulkan/vulkan.h>

namespace Vulkan::Init {
    class VulkanRenderPass {
    public:
        VulkanRenderPass();

        void        Initialize              ()                                              noexcept;

        void        createRenderPass        (VkDevice device, VkFormat swapChainImageFormat)        ;

        VkRenderPass GetRenderPass          ()                                              noexcept;

    private:
        VkRenderPass renderPass;
    };
}

#endif //BLUEPRINT_VULKANRENDERPASS_H

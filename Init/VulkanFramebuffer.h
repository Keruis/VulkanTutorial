/*
 * File:    VulkanFramebuffer.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   封装帧缓冲对象（VkFramebuffer）的创建与管理。
 *
 * Description:
 *   This header defines the VulkanFramebuffer class, which encapsulates the
 *   creation and management of VkFramebuffer objects used in the rendering
 *   pipeline. Each framebuffer corresponds to one image view in the swapchain
 *   and is tied to a render pass.
 *
 *   Vulkan 中每个渲染目标（如 Swapchain 图像）都需要绑定一个 VkFramebuffer，
 *   以与 RenderPass 搭配使用，从而完成颜色输出、清除操作等。
 *
 * Responsibilities:
 *   - createFramebuffers(): 为交换链中的每个图像视图创建 framebuffer 实例。
 *   - GetSwapChainFrameBuffers(): 提供 framebuffer 访问接口，供渲染命令使用。
 *
 * Usage:
 *   VulkanFramebuffer fb;
 *   fb.createFramebuffers(device, imageViews, renderPass, width, height);
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANFRAMEBUFFER_H
#define BLUEPRINT_VULKANFRAMEBUFFER_H

#include <vector>
#include <stdexcept>

#include <vulkan/vulkan.h>

namespace Vulkan::Init {
    class VulkanFramebuffer {
    public:
        VulkanFramebuffer       ();

        void Initialize         ()      noexcept;

        void createFramebuffers (VkDevice device, std::vector<VkImageView>& swapChainImageView, VkRenderPass renderPass, int width, int height);

        [[nodiscard]] std::vector<VkFramebuffer>&       GetSwapChainFrameBuffers() noexcept;
        [[nodiscard]] const std::vector<VkFramebuffer>& GetSwapChainFrameBuffers() const noexcept;

    private:
        std::vector<VkFramebuffer> swapChainFramebuffers;
    };
}

#endif //BLUEPRINT_VULKANFRAMEBUFFER_H


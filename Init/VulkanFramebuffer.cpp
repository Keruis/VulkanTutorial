/*
 * File:    VulkanFramebuffer.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   实现 VulkanFramebuffer 类，负责 VkFramebuffer 的创建与资源管理。
 *
 * Description:
 *   This file implements the VulkanFramebuffer class, which is responsible for
 *   creating framebuffers for each swapchain image view using the specified
 *   render pass and dimensions.
 *
 *   在 Vulkan 渲染流程中，每一个 Swapchain 图像视图（VkImageView）都必须与一个
 *   VkFramebuffer 绑定，配合 VkRenderPass 使用，才能进行渲染输出。
 *
 * Core Function:
 *   - createFramebuffers(): 为所有交换链图像视图创建 framebuffer，确保渲染目标完整。
 *
 *   若 framebuffer 数量、格式、尺寸与 render pass 不一致，将导致渲染失败或验证错误。
 *
 * Notes:
 *   此类仅负责 framebuffer 的创建与持有，不负责图像或 render pass 的生命周期管理。
 *
 * License: MIT License
 */

#include "VulkanFramebuffer.h"

Vulkan::Init::VulkanFramebuffer::VulkanFramebuffer
()
{

}


void
    Vulkan::Init::VulkanFramebuffer::Initialize
()
    noexcept
{

}


void
    Vulkan::Init::VulkanFramebuffer::createFramebuffers
(VkDevice device,
 std::vector<VkImageView>& swapChainImageView,
 VkRenderPass renderPass,
 int width,
 int height
)
{
    swapChainFramebuffers.resize(swapChainImageView.size());

    for (size_t i = 0; i < swapChainImageView.size(); i++) {
        VkImageView attachments[] = {
            swapChainImageView[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo     .sType              = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo     .renderPass         = renderPass;
        framebufferInfo     .attachmentCount    = 1;
        framebufferInfo     .pAttachments       = attachments;
        framebufferInfo     .width              = width;
        framebufferInfo     .height             = height;
        framebufferInfo     .layers             = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

std::vector<VkFramebuffer> &Vulkan::Init::VulkanFramebuffer::GetSwapChainFrameBuffers() noexcept {
    return swapChainFramebuffers;
}

const std::vector<VkFramebuffer> &Vulkan::Init::VulkanFramebuffer::GetSwapChainFrameBuffers() const noexcept {
    return swapChainFramebuffers;
}
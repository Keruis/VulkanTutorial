/*
 * File:    VulkanRenderPass.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   实现 VulkanRenderPass 类，用于配置渲染通道（Render Pass）。
 *
 * Description:
 *   This file implements the VulkanRenderPass class defined in VulkanRenderPass.h.
 *   The render pass defines how rendering operations write to framebuffers, and
 *   is essential for configuring attachment formats, load/store operations, and
 *   subpass behavior in Vulkan.
 *
 *   渲染通道（VkRenderPass）控制渲染目标的读取、写入和清除行为，
 *   是 Vulkan 渲染流程中的基础步骤。
 *   本实现创建了一个仅包含颜色附件的简单渲染通道，适用于交换链输出。
 *
 * Highlights:
 *   - 设置颜色附件（color attachment）格式、清除操作（loadOp）
 *   - 配置单一子通道（subpass）绑定图形管线
 *   - 设置子通道依赖项，确保同步顺序正确（layout transition）
 *
 * Example Usage:
 *   VulkanRenderPass pass;
 *   pass.createRenderPass(device, swapchain_format);
 *   VkRenderPass rp = pass.GetRenderPass();
 *
 * License: MIT License
 */

#include "VulkanRenderPass.h"

Vulkan::Init::VulkanRenderPass::VulkanRenderPass
()
{

}


void
    Vulkan::Init::VulkanRenderPass::Initialize
()
    noexcept
{

}


void
    Vulkan::Init::VulkanRenderPass::createRenderPass
(VkDevice device, VkFormat swapChainImageFormat)
{
    VkAttachmentDescription colorAttachment{};
    colorAttachment         .format                 = swapChainImageFormat;
    colorAttachment         .samples                = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment         .loadOp                 = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment         .storeOp                = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment         .stencilLoadOp          = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment         .stencilStoreOp         = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment         .initialLayout          = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment         .finalLayout            = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference   colorAttachmentRef{};
    colorAttachmentRef      .attachment             = 0;
    colorAttachmentRef      .layout                 = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription    subpass{};
    subpass                 .pipelineBindPoint      = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass                 .colorAttachmentCount   = 1;
    subpass                 .pColorAttachments      = &colorAttachmentRef;

    VkSubpassDependency     dependency{};
    dependency              .srcSubpass             = VK_SUBPASS_EXTERNAL;
    dependency              .dstSubpass             = 0;
    dependency              .srcStageMask           = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency              .srcAccessMask          = 0;
    dependency              .dstStageMask           = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency              .dstAccessMask          = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo  renderPassInfo{};
    renderPassInfo          .sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo          .attachmentCount        = 1;
    renderPassInfo          .pAttachments           = &colorAttachment;
    renderPassInfo          .subpassCount           = 1;
    renderPassInfo          .pSubpasses             = &subpass;
    renderPassInfo          .dependencyCount        = 1;
    renderPassInfo          .pDependencies          = &dependency;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }
}

VkRenderPass Vulkan::Init::VulkanRenderPass::GetRenderPass() noexcept {
    return renderPass;
}
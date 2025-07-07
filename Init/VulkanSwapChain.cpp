/*
 * File:    VulkanSwapChain.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   实现 VulkanSwapChain 类，封装交换链与图像视图的创建逻辑。
 *
 * Description:
 *   This file implements the VulkanSwapChain class defined in VulkanSwapChain.h.
 *   The class encapsulates all steps related to creating and configuring the swap chain,
 *   including image format selection, present mode selection, extent determination,
 *   and the creation of image views required by the rendering pipeline.
 *
 * 该文件负责完成以下关键 Vulkan 渲染初始化流程：
 *   - 创建 VkSwapchainKHR（交换链）
 *   - 根据 surface 支持情况选择最佳格式、分辨率和呈现模式
 *   - 提取交换链中的 VkImage，并为每个图像创建 VkImageView 以供渲染使用
 *
 * Highlights:
 *   - Uses surface capability query to determine swap extent and format
 *   - Supports multiple present modes (e.g., FIFO, MAILBOX)
 *   - Performs image view creation for each swapchain image
 *
 * License: MIT License
 */


#include "VulkanSwapChain.h"

Vulkan::Init::VulkanSwapChain::VulkanSwapChain
()
{

}


void
    Vulkan::Init::VulkanSwapChain::Initialize
()
    noexcept
{

}


void
    Vulkan::Init::VulkanSwapChain::createSwapChain
(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr, int width, int height)
{
    SwapChainSupportDetails swapChainSupport    =       Vulkan::Init::Utils::querySwapChainSupport(physicalDevice, surfaceKhr);

    VkSurfaceFormatKHR      surfaceFormat       =       chooseSwapSurfaceFormat (swapChainSupport                         .formats);
    VkPresentModeKHR        presentMode         =       chooseSwapPresentMode   (swapChainSupport                    .presentModes);
    VkExtent2D              extent              =       chooseSwapExtent        (swapChainSupport     .capabilities, width, height);

    uint32_t                imageCount          =       swapChainSupport        .capabilities   .minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport   .capabilities   .maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo          .sType                  =       VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo          .surface                =       surfaceKhr;

    createInfo          .minImageCount          =       imageCount;
    createInfo          .imageFormat            =       surfaceFormat.format;
    createInfo          .imageColorSpace        =       surfaceFormat.colorSpace;
    createInfo          .imageExtent            =       extent;
    createInfo          .imageArrayLayers       =       1;
    createInfo          .imageUsage             =       VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    Vulkan::Init::QueueFamilyIndices indices    =       Vulkan::Init::Utils::findQueueFamilies(physicalDevice, surfaceKhr);
    uint32_t queueFamilyIndices[]               =       {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo      .imageSharingMode       =       VK_SHARING_MODE_CONCURRENT;
        createInfo      .queueFamilyIndexCount  =       2;
        createInfo      .pQueueFamilyIndices    =       queueFamilyIndices;
    } else {
        createInfo      .imageSharingMode       =       VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo          .preTransform           =       swapChainSupport.capabilities.currentTransform;
    createInfo          .compositeAlpha         =       VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo          .presentMode            =       presentMode;
    createInfo          .clipped                =       VK_TRUE;

    createInfo          .oldSwapchain           =       VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR         (device, m_swapChain, &imageCount, nullptr);
    swapChainImages                 .resize(imageCount);
    vkGetSwapchainImagesKHR         (device, m_swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat        =       surfaceFormat.format;
    swapChainExtent             =       extent;
}


void
    Vulkan::Init::VulkanSwapChain::createImageViews
(VkDevice device)
{
    swapChainImageViews.resize(swapChainImages.size());

    for (size_t i = 0; i < swapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo{};
        createInfo      .sType                          = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo      .image                          = swapChainImages[i];
        createInfo      .viewType                       = VK_IMAGE_VIEW_TYPE_2D;
        createInfo      .format                         = swapChainImageFormat;
        createInfo      .components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo      .components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo      .components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo      .components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo      .subresourceRange.aspectMask        = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo      .subresourceRange.baseMipLevel      = 0;
        createInfo      .subresourceRange.levelCount        = 1;
        createInfo      .subresourceRange.baseArrayLayer    = 0;
        createInfo      .subresourceRange.layerCount        = 1;

        if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }
}


VkSurfaceFormatKHR
    Vulkan::Init::VulkanSwapChain::chooseSwapSurfaceFormat
(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
    auto it = std::ranges::find_if(availableFormats, [](const VkSurfaceFormatKHR& availableFormat) -> bool {
        return availableFormat      .format         ==      VK_FORMAT_B8G8R8A8_SRGB &&
               availableFormat      .colorSpace     ==      VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    });

    if (it != availableFormats.end()) {
        return *it;
    }

    return availableFormats[0];
}


VkPresentModeKHR
    Vulkan::Init::VulkanSwapChain::chooseSwapPresentMode
(const std::vector<VkPresentModeKHR> &availablePresentModes)
{
    auto it = std::ranges::find_if(availablePresentModes, [](const VkPresentModeKHR& availablePresentMode) -> bool {
        return availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR;
    });

    if (it != availablePresentModes.end()) {
        return *it;
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}


VkExtent2D
    Vulkan::Init::VulkanSwapChain::chooseSwapExtent
(const VkSurfaceCapabilitiesKHR &capabilities, int width, int height)
{
    constexpr auto MAX_U32 = std::numeric_limits<uint32_t>::max();
    if (capabilities.currentExtent.width != MAX_U32)
        return capabilities.currentExtent;

    auto [minW, minH] = capabilities.minImageExtent;
    auto [maxW, maxH] = capabilities.maxImageExtent;

    return VkExtent2D {
            std::clamp(static_cast<uint32_t>(width),  minW, maxW),
            std::clamp(static_cast<uint32_t>(height), minH, maxH)
    };
}


std::vector<VkImageView> &Vulkan::Init::VulkanSwapChain::GetSwapChainImageViews() noexcept {
    return swapChainImageViews;
}

VkSwapchainKHR Vulkan::Init::VulkanSwapChain::GetSwapChain() noexcept {
    return m_swapChain;
}

VkFormat Vulkan::Init::VulkanSwapChain::GetSwapChainImageFormat() noexcept {
    return swapChainImageFormat;
}

VkExtent2D Vulkan::Init::VulkanSwapChain::GetExtent2D() noexcept {
    return swapChainExtent;
}
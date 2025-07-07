/*
 * File:    VulkanSwapChain.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   封装 Vulkan 中交换链（VkSwapchainKHR）与图像视图的创建与管理。
 *
 * Description:
 *   This header defines the VulkanSwapChain class, which encapsulates
 *   the creation and configuration of the swap chain and its associated
 *   image views used in the Vulkan rendering pipeline.
 *
 *   交换链（SwapChain）是 Vulkan 呈现图像的核心机制，它负责：
 *     - 创建帧缓冲所需的图像（VkImage）
 *     - 配置呈现模式、颜色格式、显示分辨率等
 *     - 创建每个图像对应的 VkImageView，用于渲染管线中引用
 *
 * Responsibilities:
 *   - createSwapChain(): 创建交换链及其图像
 *   - createImageViews(): 为每帧图像创建视图
 *   - 选择最佳的格式、呈现模式与分辨率
 *
 * Accessors:
 *   - GetSwapChain(): 获取交换链句柄
 *   - GetSwapChainImageViews(): 获取图像视图数组
 *   - GetExtent2D(): 获取当前窗口分辨率
 *   - GetSwapChainImageFormat(): 获取颜色格式
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANSWAPCHAIN_H
#define BLUEPRINT_VULKANSWAPCHAIN_H

#include <numeric>
#include <algorithm>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include "VulkanStruct.h"
#include "VulkanFuncUtils.h"

namespace Vulkan::Init {
    class VulkanSwapChain {
    public:
        VulkanSwapChain();

        void        Initialize          ()                                                                                                      noexcept;

        void        createSwapChain     (VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr, int width, int height)              ;
        void        createImageViews    (VkDevice device)                                                                                               ;

        std::vector<VkImageView>&       GetSwapChainImageViews      ()      noexcept;
        VkSwapchainKHR                  GetSwapChain                ()      noexcept;
        VkFormat                        GetSwapChainImageFormat     ()      noexcept;
        VkExtent2D                      GetExtent2D                 ()      noexcept;

    private:
        VkSurfaceFormatKHR      chooseSwapSurfaceFormat         (const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR        chooseSwapPresentMode           (const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D              chooseSwapExtent                (const VkSurfaceCapabilitiesKHR& capabilities, int width, int height);

    private:
        VkSwapchainKHR              m_swapChain;
        std::vector<VkImage>        swapChainImages;
        VkFormat                    swapChainImageFormat;
        VkExtent2D                  swapChainExtent;

        std::vector<VkImageView>    swapChainImageViews;
    };
}

#endif //BLUEPRINT_VULKANSWAPCHAIN_H

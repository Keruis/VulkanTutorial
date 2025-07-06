/*
 * File:    VulkanDevice.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   封装 Vulkan 物理设备选择与逻辑设备（VkDevice）创建。
 *
 * Description:
 *   This header defines the VulkanDevice class, responsible for selecting
 *   a suitable physical device (GPU) and creating the corresponding logical
 *   device and queues (graphics & presentation) used throughout the Vulkan pipeline.
 *
 *   本类是 Vulkan 初始化流程中的核心组件之一，封装了：
 *     - 物理设备选择（pickPhysicalDevice）
 *     - 检查扩展支持与功能完整性（isDeviceSuitable）
 *     - 创建逻辑设备及图形/显示队列（createLogicalDevice）
 *
 * Public Interface:
 *   - GetDevice() 返回 VkDevice（逻辑设备句柄）
 *   - GetPhysicalDevice() 返回物理设备
 *   - GetGraphicsQueue() / GetPresentQueue() 获取对应队列
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANDEVICE_H
#define BLUEPRINT_VULKANDEVICE_H

#include <set>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm>

#include <vulkan/vulkan.h>

#include "utils/KDebug.h"
#include "VulkanConfig.h"
#include "VulkanStruct.h"
#include "VulkanFuncUtils.h"
#include "utils/VulkanUtilsDevice.h"
#include "utils/VulkanConstexprUtils.h"

namespace Vulkan::Init {
    class VulkanDevice {
    public:
        VulkanDevice();

        void                            Initialize                      ()                                                      noexcept;

        void                            pickPhysicalDevice              (VkInstance instance, VkSurfaceKHR surfaceKhr)                  ;
        void                            createLogicalDevice             (VkSurfaceKHR surfaceKhr)                                       ;

        VkDevice                        GetDevice                       ()                                                      noexcept;
        VkPhysicalDevice                GetPhysicalDevice               ()                                                      noexcept;
        [[nodiscard]] const VkQueue&    GetGraphicsQueue                ()                                                const noexcept;
        [[nodiscard]] const VkQueue&    GetPresentQueue                 ()                                                const noexcept;

    private:
        static bool                     isDeviceSuitable                (VkPhysicalDevice device, VkSurfaceKHR surfaceKhr)      noexcept;
        static bool                     checkDeviceExtensionSupport     (VkPhysicalDevice device)                               noexcept;

    private:
        VkDevice m_device                   =       VK_NULL_HANDLE;
        VkPhysicalDevice m_physicalDevice   =       VK_NULL_HANDLE;
        VkQueue                                     m_graphicsQueue;
        VkQueue                                     m_presentQueue;
    };
}

#endif //BLUEPRINT_VULKANDEVICE_H

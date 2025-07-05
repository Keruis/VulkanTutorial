/*
 * File:    VulkanUtils.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   Vulkan 枚举工具函数封装。
 *
 * Description:
 *   This header provides a generic utility function template
 *   `K_vkEnumerateVector` that simplifies the common Vulkan
 *   enumeration pattern (count + data retrieval).
 *
 *   本工具函数用于简化 Vulkan 中的枚举接口调用流程，如扩展、物理设备、
 *   表面格式等场景。它封装了两次调用：一次获取数量，一次获取数据，
 *   提高代码可读性与安全性，避免手动管理 buffer。
 *
 * Usage:
 *     auto extensions = K_vkEnumerateVector<VkExtensionProperties>(
 *         vkEnumerateInstanceExtensionProperties);
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANUTILS_H
#define BLUEPRINT_VULKANUTILS_H

#include <vector>
#include <cstdint>

#include <stdexcept>

#include <vulkan/vulkan.h>

namespace Vulkan::Utils {
    template <typename Ty_, typename Fn_>
    [[nodiscard]] std::vector<Ty_> K_vkEnumerateVector
        (Fn_ enumerateFn) 
    {
        uint32_t count = 0;
        if (enumerateFn(&count, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("Failed to enumerate Vulkan items (count)");
        }
        std::vector<Ty_> result(count);
        if (count > 0 && enumerateFn(&count, result.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to enumerate Vulkan items (data).");
        }
        return result;
    }
}

#endif //BLUEPRINT_VULKANUTILS_H
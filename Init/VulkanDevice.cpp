/*
 * File:    VulkanDevice.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   VulkanDevice 类的实现，完成物理设备选择与逻辑设备初始化。
 *
 * Description:
 *   This file implements the VulkanDevice class declared in VulkanDevice.h.
 *   It performs the following tasks in the Vulkan initialization pipeline:
 *
 *     - Enumerates and selects a suitable physical device (GPU)
 *     - Checks for required device extensions and queue support
 *     - Creates a logical device with necessary queues (graphics, present)
 *     - Provides accessors to retrieve VkDevice, VkPhysicalDevice, and VkQueue
 *
 *   本文件中封装了完整的设备初始化逻辑，保证选出的设备支持：
 *     - VK_KHR_swapchain 扩展
 *     - 图形队列与呈现队列支持（可同一或分开）
 *     - 符合验证层和功能完整性要求
 *
 * Related Functions:
 *   - isDeviceSuitable()：判断设备是否满足功能和扩展需求
 *   - checkDeviceExtensionSupport()：检测设备扩展支持
 *
 * License: MIT License
 */

#include "VulkanDevice.h"
#include "VulkanStruct.h"

Vulkan::Init::VulkanDevice::VulkanDevice
        ()
{

}

void
Vulkan::Init::VulkanDevice::Initialize
        ()
noexcept
{

}


void
Vulkan::Init::VulkanDevice::pickPhysicalDevice
        (VkInstance instance, VkSurfaceKHR surfaceKhr)
{
    uint32_t    deviceCount         =       0;
    vkEnumeratePhysicalDevices      (instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice>   devices(deviceCount);
    vkEnumeratePhysicalDevices      (instance, &deviceCount, devices.data());
    auto suitableDevice = std::ranges::find_if(devices, [&](const auto& device) {
        return isDeviceSuitable(device, surfaceKhr);
    });

    if (suitableDevice == devices.end()) {
        std::size_t i = 0;
        std::string failedList = std::ranges::fold_left(
            devices, std::string{},
            [&](const std::string& acc, const auto& d) {
                std::size_t index = i++;
                const auto name = Utils::GetDeviceName(d);
                const auto type = Utils::GetDeviceTypeString(d);
                const auto vram = Utils::GetDeviceVRAM_MB(d);

                return acc +
                       std::format("[{}] Name: {}\n    Type: {}\n    VRAM: {:.1f} MB\n\n",
                                    index, name, type, vram
                       );
            }
        );
        std::cerr << failedList;
        throw std::runtime_error("No suitable Vulkan GPU found. Checked:\n" + failedList);
    }

    m_physicalDevice = *suitableDevice;
}

void
Vulkan::Init::VulkanDevice::createLogicalDevice
        (VkSurfaceKHR surfaceKhr)
{
    QueueFamilyIndices      indices                 =       Utils::findQueueFamilies(m_physicalDevice, surfaceKhr);

    constexpr float queuePriority = 1.0f;
    std::set<uint32_t> uniqueQueueFamilies = {
            indices.graphicsFamily.value(),
            indices.presentFamily.value()
    };

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos =
        uniqueQueueFamilies
        | std::views::transform([&](uint32_t familyIndex) {
            return VkDeviceQueueCreateInfo{
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                .pNext = nullptr,
                .flags = 0,
                .queueFamilyIndex = familyIndex,
                .queueCount = 1,
                .pQueuePriorities = &queuePriority
            };
        })
        | std::ranges::to<std::vector>();

    VkPhysicalDeviceFeatures        deviceFeatures{};

    VkDeviceCreateInfo              createInfo{};
    createInfo      .sType                  =       VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo      .queueCreateInfoCount   =       static_cast<uint32_t>(queueCreateInfos.size());
    createInfo      .pQueueCreateInfos      =       queueCreateInfos.data();

    createInfo      .pEnabledFeatures       =       &deviceFeatures;

    createInfo      .enabledExtensionCount  =       static_cast<uint32_t>(deviceExtensions.size());
    createInfo      .ppEnabledExtensionNames=       deviceExtensions.data();

    Vulkan::Utils::K_constexpr_if<enableValidationLayers>(
            [&](){
                createInfo          .enabledLayerCount      =       static_cast<uint32_t>(validationLayers.size());
                createInfo          .ppEnabledLayerNames    =       validationLayers.data();
            },
            [&](){
                createInfo          .enabledLayerCount      =       0;
            }
    );

    if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue    (m_device, indices.graphicsFamily   .value(), 0, &m_graphicsQueue);
    vkGetDeviceQueue    (m_device, indices.presentFamily    .value(), 0, &m_presentQueue);
}


VkDevice
Vulkan::Init::VulkanDevice::GetDevice
        ()
noexcept
{
    return m_device;
}


VkPhysicalDevice
Vulkan::Init::VulkanDevice::GetPhysicalDevice
        ()
noexcept
{
    return m_physicalDevice;
}

const VkQueue &
Vulkan::Init::VulkanDevice::GetGraphicsQueue
        ()
const noexcept
{
    return m_graphicsQueue;
}

const VkQueue &
Vulkan::Init::VulkanDevice::GetPresentQueue
        ()
const noexcept
{
    return m_presentQueue;
}


bool
Vulkan::Init::VulkanDevice::isDeviceSuitable
        (VkPhysicalDevice device, VkSurfaceKHR surfaceKhr)
noexcept
{
    QueueFamilyIndices      indices                 =       Utils::findQueueFamilies        (device, surfaceKhr);
    bool                    extensionsSupported     =       checkDeviceExtensionSupport     (device);

    bool                    swapChainAdequate       =       false;
    if (extensionsSupported) {
        SwapChainSupportDetails     swapChainSupport    =   Init::Utils::querySwapChainSupport(device, surfaceKhr);
        swapChainAdequate                               =   !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool
Vulkan::Init::VulkanDevice::checkDeviceExtensionSupport
        (VkPhysicalDevice device)
noexcept
{
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    auto availableNames = availableExtensions
                          | std::views::transform([](const VkExtensionProperties& ext) {
        return std::string_view(ext.extensionName);  // 避免 copy
    });

    return std::ranges::all_of(deviceExtensions, [&](const std::string& required) {
        return std::ranges::find(availableNames, required) != std::ranges::end(availableNames);
    });
}

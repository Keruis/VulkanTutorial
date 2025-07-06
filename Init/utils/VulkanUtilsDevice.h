#ifndef DEMO_VULKANUTILSDEVICE_H
#define DEMO_VULKANUTILSDEVICE_H

#include <vulkan/vulkan.h>
#include <string>

namespace Vulkan::Init::Utils {

    inline std::string GetDeviceName(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties props{};
        vkGetPhysicalDeviceProperties(device, &props);
        return props.deviceName;
    }

    inline std::string DeviceTypeToString(VkPhysicalDeviceType type) {
        switch (type) {
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:  return "Integrated GPU";
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:    return "Discrete GPU";
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:     return "Virtual GPU";
            case VK_PHYSICAL_DEVICE_TYPE_CPU:             return "CPU";
            default:                                      return "Other";
        }
    }

    inline std::string GetDeviceTypeString(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties props{};
        vkGetPhysicalDeviceProperties(device, &props);
        return DeviceTypeToString(props.deviceType);
    }

    inline double GetDeviceVRAM_MB(VkPhysicalDevice device) {
        VkPhysicalDeviceMemoryProperties memProps{};
        vkGetPhysicalDeviceMemoryProperties(device, &memProps);

        uint64_t totalVRAM = 0;
        for (uint32_t i = 0; i < memProps.memoryHeapCount; ++i) {
            if (memProps.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                totalVRAM += memProps.memoryHeaps[i].size;
            }
        }

        return static_cast<double>(totalVRAM) / (1024.0 * 1024.0);  // 转为 MB
    }
}

#endif //DEMO_VULKANUTILSDEVICE_H

/*
 * File:    VulkanPipeline.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   封装图形管线（VkPipeline）与描述符布局（Descriptor Set Layout）的初始化。
 *
 * Description:
 *   This header defines the VulkanPipeline class, which encapsulates the creation
 *   of the Vulkan graphics pipeline, descriptor set layouts, descriptor pool, and
 *   descriptor sets required for uniform buffers.
 *
 *   VulkanPipeline 类是图形渲染流程的核心，负责以下组件的初始化与绑定：
 *     - 着色器模块（Shader Modules）加载
 *     - 图形管线状态配置（Graphics Pipeline Configuration）
 *     - 描述符布局（Descriptor Set Layout）创建
 *     - 描述符池与描述符集分配（Descriptor Pool & Sets）
 *
 *   本类支持多帧渲染场景下，每帧使用独立的 Uniform 缓冲描述符集。
 *
 * Main Responsibilities:
 *   - readFile(): Load SPIR-V shader binaries from disk
 *   - createShaderModule(): Wrap vkCreateShaderModule
 *   - createGraphicsPipeline(): Configure and create VkPipeline
 *   - createDescriptorSetLayout(): Define layout for uniform buffer descriptors
 *   - createDescriptorSets(): Allocate and bind uniform buffer to shaders
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANPIPELINE_H
#define BLUEPRINT_VULKANPIPELINE_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include "../App/Vertex.h"
#include "config.h"
#include "../App/UniformBufferObject.h"

namespace Vulkan::Init {
    class VulkanPipeline {
    public:
        VulkanPipeline();

        void Initialize() noexcept;

        void createDescriptorSetLayout      (VkDevice device);
        void createGraphicsPipeline         (VkDevice device, VkRenderPass renderPass);
        void createDescriptorPool           (VkDevice device);
        void createDescriptorSets           (VkDevice device, std::vector<std::vector<VkBuffer>>& uniformBuffers);

        VkPipelineLayout                           GetPipelineLayout           () noexcept;
        VkPipeline                                 GetGraphicsPipeline         () noexcept;
        VkDescriptorPool                           GetDescriptorPool           () noexcept;
        VkDescriptorSetLayout                      GetVkDescriptorSetLayout    () noexcept;
        std::vector<std::vector<VkDescriptorSet>>& GetDescriptorSets           () noexcept;

    private:
        static std::vector<char> readFile(const std::string& filename) {
            std::ifstream file(filename, std::ios::ate | std::ios::binary);

            if (!file.is_open()) {
                throw std::runtime_error("failed to open file!");
            }

            size_t fileSize = (size_t) file.tellg();
            std::vector<char> buffer(fileSize);

            file.seekg(0);
            file.read(buffer.data(), fileSize);

            file.close();

            return buffer;
        }

        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code) {
            VkShaderModuleCreateInfo createInfo{};
            createInfo      .sType      =   VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo      .codeSize   =   code.size();
            createInfo      .pCode      =   reinterpret_cast<const uint32_t*>(code.data());

            VkShaderModule shaderModule;
            if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
                throw std::runtime_error("failed to create shader module!");
            }

            return shaderModule;
        }

    private:
        VkDescriptorPool descriptorPool;
        std::vector<std::vector<VkDescriptorSet>> descriptorSets;
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
    };
}

#endif //BLUEPRINT_VULKANPIPELINE_H

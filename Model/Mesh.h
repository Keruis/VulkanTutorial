/*
 * File:    Mesh.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   封装顶点/索引缓冲与 Uniform 缓冲资源的 Mesh 类。
 *
 * Description:
 *   This header defines the Mesh class used in the rendering pipeline.
 *   It manages GPU resources including:
 *     - Vertex buffer and memory
 *     - Index buffer and memory
 *     - Uniform buffers (UBOs) per frame in flight
 *
 *   Mesh 类负责为渲染对象分配 Vulkan 缓冲资源，包括顶点数据、索引数据，
 *   以及逐帧更新的 Uniform 数据。每个 Mesh 实例代表一组几何体与其变换信息。
 *
 * Key Features:
 *   - createVertexBuffer / createIndexBuffer: 创建 GPU 缓冲区
 *   - createUniformBuffers: 每帧分配独立的 UBO
 *   - cleanup: 清理所有与该 mesh 绑定的 Vulkan 资源
 *   - 支持通过 Get 函数访问缓冲区句柄与映射内存
 *
 * Dependencies:
 *   - Vertex.h: 顶点结构定义
 *   - UniformBufferObject.h: UBO 数据结构
 *   - Memory.h: 自定义 Vulkan 内存分配工具
 *
 * License: MIT License
 */

#ifndef DEMO_MESH_H
#define DEMO_MESH_H

#include <span>
#include <ranges>
#include <cstring>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include "../App/Vertex.h"
#include "../Init/utils/Memory.h"
#include "../Math/MMat.h"
#include "../Init/config.h"
#include "../App/UniformBufferObject.h"

class Mesh {
public:
    void createVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue graphicsQueue, VkCommandPool commandPool);
    void createIndexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue graphicsQueue, VkCommandPool commandPool);
    void createUniformBuffers(VkDevice device, VkPhysicalDevice physicalDevice);

    [[nodiscard]] VkBuffer                      GetVertexBuffer             () const noexcept;
    [[nodiscard]] VkBuffer                      GetIndexBuffer              () const noexcept;
    [[nodiscard]] uint32_t                      GetVertexSize               () const noexcept;
    [[nodiscard]] uint32_t                      GetIndexSize                () const noexcept;
    [[nodiscard]] std::vector<VkBuffer>&        GetUniformBuffers           ()       noexcept;
    [[nodiscard]] std::vector<VkDeviceMemory>&  GetUniformBuffersMemory     ()       noexcept;
    [[nodiscard]] std::vector<void*>&           GetUniformBuffersMapped     ()       noexcept;
    [[nodiscard]] const std::vector<void*>&     GetUniformBuffersMapped     () const noexcept;

    void cleanup(VkDevice device) noexcept;

private:
    void copyBuffer(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    static void createBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

public:
    std::vector<Vertex>             vertices;
    const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
    };

    UniformBufferObject             ubo;

    VkBuffer                        vertexBuffer;
    VkDeviceMemory                  vertexBufferMemory;
    VkBuffer                        indexBuffer;
    VkDeviceMemory                  indexBufferMemory;

    std::vector<VkBuffer>           uniformBuffers;
    std::vector<VkDeviceMemory>     uniformBuffersMemory;
    std::vector<void*>              uniformBuffersMapped;
};


#endif //DEMO_MESH_H

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

#include "Mesh.h"

void
    Mesh::createBuffer
(VkDevice                   device,
 VkPhysicalDevice           physicalDevice,
 VkDeviceSize               size,
 VkBufferUsageFlags         usage,
 VkMemoryPropertyFlags      properties,
 VkBuffer&                  buffer,
 VkDeviceMemory&            bufferMemory)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo              .sType              =           VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo              .size               =           size;
    bufferInfo              .usage              =           usage;
    bufferInfo              .sharingMode        =           VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements   (device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo               .sType              =           VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo               .allocationSize     =           memRequirements.size;
    allocInfo               .memoryTypeIndex    =           findMemoryType(memRequirements.memoryTypeBits, properties, physicalDevice);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory              (device, buffer, bufferMemory, 0);
}


void
    Mesh::createVertexBuffer
(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue graphicsQueue, VkCommandPool commandPool)
{
    VkDeviceSize        bufferSize      =       sizeof(vertices[0]) * vertices.size();

    VkBuffer            stagingBuffer;
    VkDeviceMemory      stagingBufferMemory;
    createBuffer        (device, physicalDevice, bufferSize,
                         VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         stagingBuffer, stagingBufferMemory);

    void*               data;
    vkMapMemory         (device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy              (data, vertices.data(), (size_t) bufferSize);
    vkUnmapMemory       (device, stagingBufferMemory);

    createBuffer        (device, physicalDevice, bufferSize,
                         VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                         vertexBuffer, vertexBufferMemory);

    copyBuffer          (device, graphicsQueue, commandPool, stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer     (device, stagingBuffer, nullptr);
    vkFreeMemory        (device, stagingBufferMemory, nullptr);
}

void
    Mesh::createIndexBuffer
(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue graphicsQueue, VkCommandPool commandPool)
{
    VkDeviceSize        bufferSize      =       sizeof(indices[0]) * indices.size();

    VkBuffer            stagingBuffer;
    VkDeviceMemory      stagingBufferMemory;
    createBuffer        (device, physicalDevice, bufferSize,
                         VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         stagingBuffer, stagingBufferMemory);

    void*               data;
    vkMapMemory         (device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy              (data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory       (device, stagingBufferMemory);

    createBuffer        (device, physicalDevice, bufferSize,
                         VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                         indexBuffer, indexBufferMemory);

    copyBuffer          (device, graphicsQueue, commandPool, stagingBuffer, indexBuffer, bufferSize);

    vkDestroyBuffer     (device, stagingBuffer, nullptr);
    vkFreeMemory        (device, stagingBufferMemory, nullptr);
}


void
    Mesh::createUniformBuffers
(VkDevice device, VkPhysicalDevice physicalDevice)
{
    const VkDeviceSize bufferSize   =   sizeof(UniformBufferObject);

    uniformBuffers              .resize     (MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMemory        .resize     (MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped        .resize     (MAX_FRAMES_IN_FLIGHT);

    auto buffers        = std::span(uniformBuffers);
    auto memories       = std::span(uniformBuffersMemory);
    auto mappedPointers = std::span(uniformBuffersMapped);

    for (auto [buf, mem, mapped] : std::views::zip(buffers, memories, mappedPointers)) {
        createBuffer(device, physicalDevice, bufferSize,
                     VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     buf, mem);
        vkMapMemory(device, mem, 0, bufferSize, 0, &mapped);
    }
}

VkBuffer Mesh::GetVertexBuffer() const noexcept {
    return vertexBuffer;
}

uint32_t Mesh::GetVertexSize() const noexcept {
    return vertices.size();
}

VkBuffer Mesh::GetIndexBuffer() const noexcept {
    return indexBuffer;
}

uint32_t Mesh::GetIndexSize() const noexcept {
    return indices.size();
}

std::vector<VkBuffer> &Mesh::GetUniformBuffers() noexcept {
    return uniformBuffers;
}

std::vector<VkDeviceMemory> &Mesh::GetUniformBuffersMemory() noexcept {
    return uniformBuffersMemory;
}

std::vector<void *> &Mesh::GetUniformBuffersMapped() noexcept {
    return uniformBuffersMapped;
}

const std::vector<void *> &Mesh::GetUniformBuffersMapped() const noexcept {
    return uniformBuffersMapped;
}

void
    Mesh::cleanup(VkDevice device)
noexcept
{
    for (auto [buffer, memory] : std::views::zip(uniformBuffers, uniformBuffersMemory)) {
        vkDestroyBuffer     (device, buffer, nullptr);
        vkFreeMemory        (device, memory, nullptr);
    }

    vkDestroyBuffer         (device, indexBuffer, nullptr);
    vkFreeMemory            (device, indexBufferMemory, nullptr);

    vkDestroyBuffer         (device, vertexBuffer, nullptr);
    vkFreeMemory            (device, vertexBufferMemory, nullptr);
}

void
    Mesh::copyBuffer
(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo               .sType                  = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo               .level                  = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo               .commandPool            = commandPool;
    allocInfo               .commandBufferCount     = 1;

    VkCommandBuffer             commandBuffer;
    vkAllocateCommandBuffers    (device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo    beginInfo{};
    beginInfo               .sType                  = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo               .flags                  = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer        (commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion              .size                   = size;
    vkCmdCopyBuffer             (commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer          (commandBuffer);

    VkSubmitInfo                submitInfo{};
    submitInfo              .sType                  = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo              .commandBufferCount     = 1;
    submitInfo              .pCommandBuffers        = &commandBuffer;

    vkQueueSubmit               (graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle             (graphicsQueue);

    vkFreeCommandBuffers        (device, commandPool, 1, &commandBuffer);
}
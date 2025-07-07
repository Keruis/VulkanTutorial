/*
 * File:    VulkanPipeline.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   实现 VulkanPipeline 类，用于初始化图形管线及描述符布局。
 *
 * Description:
 *   This file implements the VulkanPipeline class declared in VulkanPipeline.h.
 *   It handles the setup of the Vulkan graphics pipeline, including:
 *     - Vertex and fragment shader loading
 *     - Pipeline layout creation
 *     - Descriptor set layout (uniform buffer) setup
 *     - Descriptor pool and descriptor set allocation
 *
 *   VulkanPipeline 是渲染流程中的关键模块，定义了 GPU 如何解释与处理顶点数据、
 *   如何与 Uniform Buffer 交互，并最终输出图像到屏幕。
 *
 * Key Functions:
 *   - createGraphicsPipeline(): 配置顶点输入、输入装配、光栅化等状态，并生成 VkPipeline
 *   - createDescriptorSetLayout(): 设置 Uniform Buffer 使用的布局信息
 *   - createDescriptorPool(): 为所有帧统一管理描述符资源
 *   - createDescriptorSets(): 为每个帧绑定对应的 Uniform Buffer
 *   - readFile(): 加载 SPIR-V 着色器文件
 *   - createShaderModule(): 创建 Shader 模块对象
 *
 * Notes:
 *   使用 Vulkan API 时需确保顺序正确，且资源管理得当，否则容易引发崩溃。
 *   本类封装的逻辑支持多帧缓冲（Frame in flight）下的 Uniform 分帧绑定。
 *
 * License: MIT License
 */

#include "VulkanPipeline.h"

Vulkan::Init::VulkanPipeline::VulkanPipeline
()
{

}


void
    Vulkan::Init::VulkanPipeline::Initialize\
()
    noexcept
{

}


void
    Vulkan::Init::VulkanPipeline::createDescriptorSetLayout
(VkDevice device)
{
    VkDescriptorSetLayoutBinding    uboLayoutBinding{};
    uboLayoutBinding        .binding                = 0;
    uboLayoutBinding        .descriptorCount        = 1;
    uboLayoutBinding        .descriptorType         = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding        .pImmutableSamplers     = nullptr;
    uboLayoutBinding        .stageFlags             = VK_SHADER_STAGE_VERTEX_BIT;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo              .sType                  = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo              .bindingCount           = 1;
    layoutInfo              .pBindings              = &uboLayoutBinding;

    if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}


void
    Vulkan::Init::VulkanPipeline::createGraphicsPipeline
(VkDevice device, VkRenderPass renderPass)
{
    auto vertShaderCode = readFile("shaders/vert.spv");
    auto fragShaderCode = readFile("shaders/frag.spv");

    VkShaderModule vertShaderModule = createShaderModule(device, vertShaderCode);
    VkShaderModule fragShaderModule = createShaderModule(device, fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo         .sType      =   VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo         .stage      =   VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo         .module     =   vertShaderModule;
    vertShaderStageInfo         .pName      =   "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo         .sType      =   VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo         .stage      =   VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo         .module     =   fragShaderModule;
    fragShaderStageInfo         .pName      =   "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo             .sType                              = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo             .vertexBindingDescriptionCount      = 1;
    vertexInputInfo             .vertexAttributeDescriptionCount    = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo             .pVertexBindingDescriptions         = &bindingDescription;
    vertexInputInfo             .pVertexAttributeDescriptions       = attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly               .sType                              = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly               .topology                           = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly               .primitiveRestartEnable             = VK_FALSE;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState               .sType                              = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState               .viewportCount                      = 1;
    viewportState               .scissorCount                       = 1;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer                  .sType                              = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer                  .depthClampEnable                   = VK_FALSE;
    rasterizer                  .rasterizerDiscardEnable            = VK_FALSE;
    rasterizer                  .polygonMode                        = VK_POLYGON_MODE_FILL;
    rasterizer                  .lineWidth                          = 1.0f;
    rasterizer                  .cullMode                           = VK_CULL_MODE_BACK_BIT;
    rasterizer                  .frontFace                          = VK_FRONT_FACE_CLOCKWISE;
    rasterizer                  .depthBiasEnable                    = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling               .sType                              = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling               .sampleShadingEnable                = VK_FALSE;
    multisampling               .rasterizationSamples               = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment        .colorWriteMask                     = VK_COLOR_COMPONENT_R_BIT |
                                                                      VK_COLOR_COMPONENT_G_BIT |
                                                                      VK_COLOR_COMPONENT_B_BIT |
                                                                      VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment        .blendEnable                        = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending               .sType                              = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending               .logicOpEnable                      = VK_FALSE;
    colorBlending               .logicOp                            = VK_LOGIC_OP_COPY;
    colorBlending               .attachmentCount                    = 1;
    colorBlending               .pAttachments                       = &colorBlendAttachment;
    colorBlending               .blendConstants[0]                  = 0.0f;
    colorBlending               .blendConstants[1]                  = 0.0f;
    colorBlending               .blendConstants[2]                  = 0.0f;
    colorBlending               .blendConstants[3]                  = 0.0f;

    std::vector<VkDynamicState> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
    };
    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState                .dynamicStateCount                  = static_cast<uint32_t>(dynamicStates.size());
    dynamicState                .pDynamicStates                     = dynamicStates.data();

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo          .sType                              = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo          .setLayoutCount                     = 1;
    pipelineLayoutInfo          .pSetLayouts                        = &descriptorSetLayout;

    if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo                .sType                              = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo                .stageCount                         = 2;
    pipelineInfo                .pStages                            = shaderStages;
    pipelineInfo                .pVertexInputState                  = &vertexInputInfo;
    pipelineInfo                .pInputAssemblyState                = &inputAssembly;
    pipelineInfo                .pViewportState                     = &viewportState;
    pipelineInfo                .pRasterizationState                = &rasterizer;
    pipelineInfo                .pMultisampleState                  = &multisampling;
    pipelineInfo                .pColorBlendState                   = &colorBlending;
    pipelineInfo                .pDynamicState                      = &dynamicState;
    pipelineInfo                .layout                             = pipelineLayout;
    pipelineInfo                .renderPass                         = renderPass;
    pipelineInfo                .subpass                            = 0;
    pipelineInfo                .basePipelineHandle                 = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    vkDestroyShaderModule       (device, fragShaderModule, nullptr);
    vkDestroyShaderModule       (device, vertShaderModule, nullptr);
}

void
    Vulkan::Init::VulkanPipeline::createDescriptorPool
(VkDevice device)
{
    VkDescriptorPoolSize poolSize{};
    poolSize                    .type                               = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize                    .descriptorCount                    = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * 2);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo                    .sType                              = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo                    .poolSizeCount                      = 1;
    poolInfo                    .pPoolSizes                         = &poolSize;
    poolInfo                    .maxSets                            = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * 2);

    if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}


void
Vulkan::Init::VulkanPipeline::createDescriptorSets
(
    VkDevice device,
    std::vector<std::vector<VkBuffer>>& uniformBuffers
)
{
    size_t modelCount = uniformBuffers.size();
    size_t frameCount = MAX_FRAMES_IN_FLIGHT;

    std::vector<VkDescriptorSetLayout> layouts(modelCount * frameCount, descriptorSetLayout);

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo                   .sType                              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo                   .descriptorPool                     = descriptorPool;
    allocInfo                   .descriptorSetCount                 = static_cast<uint32_t>(layouts.size());
    allocInfo                   .pSetLayouts                        = layouts.data();

    std::vector<VkDescriptorSet> flatDescriptorSets(modelCount * frameCount);
    if (vkAllocateDescriptorSets(device, &allocInfo, flatDescriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    descriptorSets.resize(modelCount);
    for (size_t model = 0; model < modelCount; ++model) {
        descriptorSets[model].resize(frameCount);
    }

    for (size_t model = 0; model < modelCount; ++model) {
        for (size_t frame = 0; frame < frameCount; ++frame) {
            size_t idx = model * frameCount + frame;
            descriptorSets[model][frame] = flatDescriptorSets[idx];
        }
    }

    for (size_t model = 0; model < modelCount; ++model) {
        for (size_t frame = 0; frame < frameCount; ++frame) {
            VkDescriptorBufferInfo bufferInfo{
                    .buffer = uniformBuffers[model][frame],
                    .offset = 0,
                    .range = sizeof(UniformBufferObject)
            };

            VkWriteDescriptorSet descriptorWrite{
                    .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                    .pNext = nullptr,
                    .dstSet = descriptorSets[model][frame],
                    .dstBinding = 0,
                    .dstArrayElement = 0,
                    .descriptorCount = 1,
                    .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                    .pImageInfo = nullptr,
                    .pBufferInfo = &bufferInfo,
                    .pTexelBufferView = nullptr
            };

            vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
        }
    }
}

VkPipeline Vulkan::Init::VulkanPipeline::GetGraphicsPipeline() noexcept {
    return graphicsPipeline;
}

VkPipelineLayout Vulkan::Init::VulkanPipeline::GetPipelineLayout() noexcept {
    return pipelineLayout;
}

VkDescriptorSetLayout Vulkan::Init::VulkanPipeline::GetVkDescriptorSetLayout() noexcept {
    return descriptorSetLayout;
}

std::vector<std::vector<VkDescriptorSet>> &Vulkan::Init::VulkanPipeline::GetDescriptorSets() noexcept {
    return descriptorSets;
}

VkDescriptorPool Vulkan::Init::VulkanPipeline::GetDescriptorPool() noexcept {
    return descriptorPool;
}
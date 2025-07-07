cmake_minimum_required(VERSION 3.16)
project(demo)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Vulkan REQUIRED)
find_package(X11 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(
        ${Vulkan_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)

link_directories(
        ${GLFW_LIBRARY_DIRS}
)

add_executable(demo 
    main.cpp
    Model/Mesh.cpp
    Camera.cpp
    CameraController.cpp
    Input.cpp
    X11.cpp

        App/VulkanApplication.cpp

        Init/utils/KDebug.cpp
        Init/VulkanContext.cpp
        Init/VulkanSync.cpp
        Init/VulkanCommand.cpp
        Init/VulkanFramebuffer.cpp
        Init/VulkanPipeline.cpp
        Init/VulkanRenderPass.cpp
        Init/VulkanFuncUtils.cpp
        Init/VulkanDevice.cpp
        Init/VulkanSurface.cpp
        Init/VulkanInstance.cpp
        Init/VulkanSwapChain.cpp
)

target_link_libraries(demo
        ${Vulkan_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${X11_LIBRARIES}
        dl
)
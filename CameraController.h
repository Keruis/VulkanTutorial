/*
 * File:    CameraController.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Renderer
 * Brief:   相机控制器类，负责将输入映射为相机移动。
 *
 * Description:
 *   This header defines the CameraController class, which takes user input
 *   (keyboard, mouse, etc.) and translates it into camera movement commands.
 *   It interacts with the Camera class to simulate first-person or free-fly
 *   camera behavior based on frame time and movement speed.
 *
 *   CameraController 类用于处理用户输入，并将其转化为对 Camera
 *   实例的移动或旋转控制。适用于第一人称视角、自由相机等场景。
 *
 * Usage:
 *     CameraController controller(&camera);
 *     controller.Update(input, deltaTime);
 *
 * License: MIT License
 */

#ifndef DEMO_CAMERACONTROLLER_H
#define DEMO_CAMERACONTROLLER_H

#include "Camera.h"
#include "Input.h"
#include "Math/MMat.h"

class CameraController {
public:
    CameraController        (Camera* camera);
    void Update             (Input& input, float deltaTime) noexcept;

private:
    Camera*     m_camera;
    float       m_moveSpeed = 2.5f;
};


#endif //DEMO_CAMERACONTROLLER_H

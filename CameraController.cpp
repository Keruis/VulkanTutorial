/*
 * File:    CameraController.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Renderer
 * Brief:   CameraController 类的实现，实现用户输入驱动的相机控制逻辑。
 *
 * Description:
 *   This file implements the CameraController class defined in CameraController.h.
 *   It reads input state (from the Input class) and updates the associated Camera's
 *   position based on directional input and movement speed scaled by frame time.
 *
 *   本文件实现了 CameraController 类的 Update 方法，处理来自 Input 类的
 *   用户输入（如键盘方向键），并根据 deltaTime 控制 Camera 对象的位置变化。
 *   支持平滑移动、帧率无关的视角控制，适用于第一人称和自由视角相机。
 *
 * License: MIT License
 */

#include "CameraController.h"

CameraController::CameraController
(Camera *camera)
    : m_camera(camera)
{

}

void 
    CameraController::Update
(Input &input, float deltaTime) 
    noexcept 
{
    auto pos    =   m_camera->GetPosition();
    float speed =   m_moveSpeed * deltaTime;

    if (input.IsKeyDown(XK_w) || input.IsKeyDown(XK_W)) pos.y -= speed;
    if (input.IsKeyDown(XK_s) || input.IsKeyDown(XK_S)) pos.y += speed;
    if (input.IsKeyDown(XK_a) || input.IsKeyDown(XK_A)) pos.x -= speed;
    if (input.IsKeyDown(XK_d) || input.IsKeyDown(XK_D)) pos.x += speed;
    if (input.IsKeyDown(XK_Shift_L) || input.IsKeyDown(XK_Shift_R)) pos.z += speed;
    if (input.IsKeyDown(XK_space)) pos.z -= speed;

    m_camera->SetPosition(pos.x, pos.y, pos.z);
}
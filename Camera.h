/*
 * File:    Camera.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Renderer
 * Brief:   定义相机类 Camera，用于视图矩阵与相机控制。
 *
 * Description:
 *   This header defines the Camera class, which handles 3D camera positioning,
 *   rotation, and the construction of view matrices. It supports standard view,
 *   base view (for UI or background), and reflection view (for water or mirrors).
 *
 *   Camera 类用于控制 3D 相机的位置与旋转，并提供构建视图矩阵的功能。
 *   包括常规视图、基础视图（BaseView）以及反射视图（ReflectionView），
 *   同时支持通过鼠标移动与位移向量进行交互控制。
 *
 * License: MIT License
 */

#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

#include "../Math/MMat.h"
#include "../Math/MVec.h"

class Camera {
public:
	Camera							();
	Camera							(const Camera&);
	~Camera							();

	void SetPosition				(float, float, float);
	void SetRotation				(float, float, float);

	Math::Vec::VecF3 GetPosition	();
	Math::Vec::VecF3 GetRotation	();

	void Render						();
	void GetViewMatrix				(Math::Mat::MatF44&);

	void RenderBaseViewMatrix		();
	void GetBaseViewMatrix			(Math::Mat::MatF44&);

	void RenderReflection			(float);
	void GetReflectionViewMatrix	(Math::Mat::MatF44&);

	void Move						(float, float, float) 	noexcept;
	void RotateByMouse				(float, float) 			noexcept;

private:
	float 				m_positionX, m_positionY, m_positionZ;
	float 				m_rotationX, m_rotationY, m_rotationZ;
	Math::Mat::MatF44 	m_viewMatrix;
	Math::Mat::MatF44 	m_baseViewMatrix;
	Math::Mat::MatF44 	m_reflectionViewMatrix;
};

#endif
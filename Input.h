/*
 * File:    Input.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Renderer
 * Brief:   跨平台输入处理类，封装键盘与鼠标输入状态。
 *
 * Description:
 *   This header defines the Input class, which handles user input across
 *   Windows and Linux platforms. It abstracts platform-specific APIs like
 *   DirectInput (Windows) and X11/XInput2 (Linux) to provide a unified
 *   interface for querying keyboard and mouse states.
 *
 *   Input 类封装了输入设备的初始化、状态读取与查询接口。
 *   提供如 IsKeyDown, IsEscapePressed, GetMouseLocation 等函数，
 *   可用于实现用户交互、控制逻辑或相机控制。
 *
 * Features:
 *   - Platform-specific backend: DirectInput or X11
 *   - Cross-platform key/mouse abstraction
 *   - Simple API for key states and mouse position
 *
 * Usage:
 *     Input input;
 *     input.Initialize(...);
 *     if (input.IsKeyDown(KEY_W)) { moveForward(); }
 *
 * License: MIT License
 */

#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

#include <cstring>
#include <unordered_set>

#ifdef _WIN32
    #include <dinput.h>
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#else
    #include <X11/Xlib.h>
    #include <X11/XKBlib.h>
    #include <X11/keysym.h>
    #include <X11/extensions/XInput2.h>
#endif

class Input {
public:
    Input                               ();
    ~Input                              ();

    bool        Initialize              (void* windowHandle, int screenWidth, int screenHeight);
    void        Shutdown                ();
    bool        Frame                   ();

    bool        IsKeyDown               (unsigned int key) noexcept;
    void        KeyDown                 (unsigned int) noexcept ;
    void        KeyUp                   (unsigned int) noexcept ;

    bool        IsEscapePressed         ();
    bool        IsLeftArrowPressed      ();
    bool        IsRightArrowPressed     ();
    bool        IsMousePressed          ();
    void        GetMouseLocation        (int& x, int& y);

private:
    bool        ReadKeyboard            ();
    bool        ReadMouse               ();
    void        ProcessInput            ();

private:
    std::unordered_set<unsigned int>        m_pressedKeys;
    int                                     m_screenWidth, m_screenHeight;
    int                                     m_mouseX, m_mouseY;

#ifdef _WIN32
    LPDIRECTINPUT8                          m_directInput;
    LPDIRECTINPUTDEVICE8                    m_keyboard;
    LPDIRECTINPUTDEVICE8                    m_mouse;
    BYTE                                    m_keyboardState[256];
    DIMOUSESTATE                            m_mouseState;
#else
    Display*                                m_display;
    Window                                  m_window;
    char                                    m_keyboardState[32];
    int                                     m_mouseDeltaX, m_mouseDeltaY;
    bool                                    m_mouseButtons[3];
#endif
};

#endif
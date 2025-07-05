/*
 * File:    Input.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Renderer
 * Brief:   Input 类的实现，封装 Windows 与 Linux 下的输入处理逻辑。
 *
 * Description:
 *   This file implements the Input class defined in Input.h. It provides the
 *   platform-specific logic to initialize input devices and query keyboard/mouse
 *   states. On Windows, it uses DirectInput API. On Linux, it relies on X11 and
 *   XInput2 to poll keyboard and mouse states.
 *
 *   本实现文件根据操作系统的不同，封装了：
 *     - Windows 平台使用 DirectInput 初始化与读取输入状态；
 *     - Linux 平台使用 X11 与 XInput2 实现键盘与鼠标事件轮询。
 *
 *   提供跨平台的一致输入接口，包括：
 *     - 按键按下检测（IsKeyDown / IsEscapePressed 等）；
 *     - 鼠标点击与位置跟踪；
 *     - 每帧更新输入状态 Frame()。
 *
 * Platform Notes:
 *   - Windows: Requires dinput8.lib, dxguid.lib
 *   - Linux: Requires Xlib, XInput2 headers and linkage
 *
 * License: MIT License
 */

#include "Input.h"

Input::Input
()
        : m_screenWidth(0), m_screenHeight(0),
          m_mouseX(0), m_mouseY(0)
#ifdef _WIN32
        , m_directInput(nullptr), m_keyboard(nullptr), m_mouse(nullptr)
#else
        , m_display(nullptr), m_window(0), m_mouseDeltaX(0), m_mouseDeltaY(0)
#endif
{
#ifdef _WIN32
    std::memset(m_keyboardState, 0, sizeof(m_keyboardState));
#else
    std::memset(m_keyboardState, 0, sizeof(m_keyboardState));
    std::memset(m_mouseButtons, 0, sizeof(m_mouseButtons));
#endif
}

Input::~Input
() 
{

}


bool 
    Input::Initialize
(void* windowHandle, int screenWidth, int screenHeight) 
{
    m_screenWidth       = screenWidth;
    m_screenHeight      = screenHeight;
    m_mouseX            = 0;
    m_mouseY            = 0;

#ifdef _WIN32
    HRESULT result;

    HWND hwnd           = static_cast<HWND>(windowHandle);

    memset              (&m_mouseState, 0, sizeof(m_mouseState));

    result              = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (void**)&m_directInput, nullptr);
    if (FAILED(result)) return false;

    result              = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr);
    if (FAILED(result)) return false;

    result              = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(result)) return false;

    result              = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    if (FAILED(result)) return false;

    result              = m_keyboard->Acquire();
    if (FAILED(result)) return false;

    result              = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, nullptr);
    if (FAILED(result)) return false;

    result              = m_mouse->SetDataFormat(&c_dfDIMouse);
    if (FAILED(result)) return false;

    result              = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(result)) return false;

    result              = m_mouse->Acquire();
    if (FAILED(result)) return false;

#else
    m_display           = XOpenDisplay(nullptr);
    if (!m_display) return false;

    m_window            = *(Window*)windowHandle;
#endif

    return true;
}

void
    Input::Shutdown
() 
{
#ifdef _WIN32
    if (m_mouse) {
        m_mouse             ->      Unacquire();
        m_mouse             ->      Release();
        m_mouse             =       nullptr;
    }

    if (m_keyboard) {
        m_keyboard          ->      Unacquire();
        m_keyboard          ->      Release();
        m_keyboard          =       nullptr;
    }

    if (m_directInput) {
        m_directInput       ->      Release();
        m_directInput       =       nullptr;
    }
#else
    if (m_display) {
        XCloseDisplay       (m_display);
        m_display           =       nullptr;
    }
#endif
}


bool 
    Input::Frame
() 
{
	bool result;

	result          = ReadKeyboard();
	if(!result) {
		return false;
	}

	result          = ReadMouse();
	if(!result) {
		return false;
	}

	ProcessInput();

	return true;
}


bool 
    Input::ReadKeyboard
() 
{
#ifdef _WIN32
    HRESULT result  = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
    if (FAILED(result)) {
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
            m_keyboard      ->      Acquire();
        } else {
            return false;
        }
    }
    return true;
#else
    if (!m_display) return false;
    char keys[32];
    XQueryKeymap        (m_display, keys);
    XQueryKeymap        (m_display, m_keyboardState);
    memcpy              (m_keyboardState, keys, 32);
    return true;
#endif
}


bool 
    Input::ReadMouse
() 
{
#ifdef _WIN32
    HRESULT result      = m_mouse   ->      GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
    if (FAILED(result)) {
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
            m_mouse     ->      Acquire();
        } else {
            return false;
        }
    }
    return true;
#else
    if (!m_display) return false;

    Window              root, child;
    int                 rootX, rootY, winX, winY;
    unsigned int        mask;

    if (!XQueryPointer(m_display, m_window, &root, &child, &rootX, &rootY, &winX, &winY, &mask))
        return false;

    static int        lastX   =   winX, 
                      lastY   =   winY;
    m_mouseDeltaX   = winX  -   lastX;
    m_mouseDeltaY   = winY  -   lastY;
    lastX           = winX;
    lastY           = winY;

    m_mouseButtons[0] = (mask & Button1Mask);

    return true;
#endif
}

void 
    Input::ProcessInput
() 
{
#ifdef _WIN32
    m_mouseX    +=      m_mouseState.lX;
    m_mouseY    +=      m_mouseState.lY;
#else
    Window          root, child;
    int             rootX, rootY, winX, winY;
    unsigned int    mask;

    if (XQueryPointer(m_display, m_window, &root, &child, &rootX, &rootY, &winX, &winY, &mask)) {
        m_mouseX    =       winX;
        m_mouseY    =       winY;
    }

    m_pressedKeys   .clear();
    for (int keycode = 0; keycode < 256; ++keycode) {
        if (m_keyboardState[keycode / 8] & (1 << (keycode % 8))) {
            KeySym keysym = XkbKeycodeToKeysym(m_display, keycode, 0, 0);
            if (keysym != NoSymbol) {
                m_pressedKeys.insert(keysym);
            }
        }
    }
#endif

    if (m_mouseX < 0)               m_mouseX = 0;
    if (m_mouseY < 0)               m_mouseY = 0;
    if (m_mouseX > m_screenWidth)   m_mouseX = m_screenWidth;
    if (m_mouseY > m_screenHeight)  m_mouseY = m_screenHeight;
}


bool 
    Input::IsEscapePressed
() 
{
#ifdef _WIN32
    return (m_keyboardState[DIK_ESCAPE] & 0x80) != 0;
#else
    KeyCode escKey = XKeysymToKeycode(m_display, XK_Escape);
    return (m_keyboardState[escKey / 8] & (1 << (escKey % 8))) != 0;
#endif
}


bool 
    Input::IsLeftArrowPressed
() 
{
#ifdef _WIN32
    return (m_keyboardState[DIK_LEFT] & 0x80) != 0;
#else
    return IsKeyDown(XK_Left);
#endif
}


bool 
    Input::IsRightArrowPressed
() 
{
#ifdef _WIN32
    return (m_keyboardState[DIK_RIGHT] & 0x80) != 0;
#else
    return IsKeyDown(XK_Right);
#endif
}


void 
    Input::GetMouseLocation
(int& mouseX, int& mouseY) 
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}


bool 
    Input::IsMousePressed
() 
{
#ifdef _WIN32
    return (m_mouseState.rgbButtons[0] & 0x80) != 0;
#else
    return m_mouseButtons[0];
#endif
}

void 
    Input::KeyDown
(unsigned int key) 
    noexcept 
{
    m_pressedKeys.insert(key);
}

void 
    Input::KeyUp
(unsigned int key) 
    noexcept 
{
    m_pressedKeys.erase(key);
}

bool 
    Input::IsKeyDown
(unsigned int key) 
    noexcept 
{
    return m_pressedKeys.count(key) > 0;
}
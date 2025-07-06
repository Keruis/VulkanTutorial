/*
 * File:    KDebug.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   简洁的调试输出工具，提供条件编译的日志宏 kDebug。
 *
 * Description:
 *   This header defines a lightweight debug output utility for the Blueprint
 *   Vulkan project. The KDebugStream class enables stream-like debug messages
 *   that include file name, line number, and function name. Logging is enabled
 *   only in debug builds (when NDEBUG is not defined).
 *
 *   本工具类用于调试模式下的日志输出，封装了可流式输出的调试信息，
 *   支持文件名、行号与函数自动标注，通过 `kDebug()` 宏启用/关闭。
 *   在 Release 模式下编译将自动禁用所有调试输出代码，避免额外开销。
 *
 * Usage:
 *     kDebug() << "Creating Vulkan instance:" << instance;
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_KDEBUG_H
#define BLUEPRINT_KDEBUG_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace Vulkan::Utils {

#ifndef NDEBUG
    #define KDEBUG_ENABLED 1
#else
    #define KDEBUG_ENABLED 0
#endif

    class KDebugStream {
    public:
        KDebugStream(const char *file, int line, const char *func);

        ~KDebugStream();

        template<typename Ty_>
        KDebugStream &operator<<(Ty_ &&val) {
#if KDEBUG_ENABLED
            m_stream << std::forward<Ty_>(val) << ' ';
#endif
            return *this;
        }

    private:
        std::ostringstream  m_stream;
        const char *        m_file;
        int                 m_line;
        const char *        m_func;
    };
}
#if KDEBUG_ENABLED
    #define kDebug() ::Vulkan::Utils::KDebugStream(__FILE__, __LINE__, __func__)
#else
    class KDebugNoOp {
    public:
        template<typename T> constexpr KDebugNoOp& operator<<(T&&) { return *this; }
    };
    #define kDebug() KDebugNoOp()
#endif

#endif //BLUEPRINT_KDEBUG_H

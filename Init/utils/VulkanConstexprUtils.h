/*
 * File:    VulkanConstexprUtils.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   编译期条件分支封装工具（constexpr if）。
 *
 * Description:
 *   This header provides lightweight wrappers for compile-time conditional
 *   execution using `if constexpr`. The `K_constexpr_if` function templates
 *   allow clearer and reusable branching logic during template metaprogramming
 *   or constexpr-based scenarios.
 *
 *   该工具将 `if constexpr` 条件分支进行封装，提供统一的函数式接口，
 *   可用于在模板或编译期上下文中执行不同逻辑，增强代码清晰度和可复用性。
 *
 * Usage:
 *     K_constexpr_if<is_integral<T>>(
 *         [] {  then  },
 *         [] {  else  }
 *     );
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANCONSTEXPRUTILS_H
#define BLUEPRINT_VULKANCONSTEXPRUTILS_H

namespace Vulkan::Utils {
    template <bool Cond, typename ThenFn, typename ElseFn>
    constexpr void K_constexpr_if
            (ThenFn&& then_fn, ElseFn&& else_fn)
    {
        if constexpr (Cond) {
            then_fn();
        } else {
            else_fn();
        }
    }

    template <bool Cond, typename ThenFn>
    constexpr void K_constexpr_if
            (ThenFn&& then_fn)
    {
        if constexpr (Cond) {
            then_fn();
        }
    }
}

#endif //BLUEPRINT_VULKANCONSTEXPRUTILS_H

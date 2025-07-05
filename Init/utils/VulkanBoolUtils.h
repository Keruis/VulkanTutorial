/*
 * File:    VulkanBoolUtils.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   提供函数式链式布尔逻辑判断工具。
 *
 * Description:
 *   This header defines BoolConditionResult, a functional-style wrapper
 *   around boolean expressions that supports method chaining via `then` and
 *   `otherwise` callbacks. It also provides utility functions like
 *   `K_MixedAll`, `K_MixedAny`, and `K_MixedNone` for evaluating multiple
 *   conditions in a concise, expressive manner.
 *
 *   该模块通过 `BoolConditionResult` 实现了布尔逻辑的链式回调表达，
 *   可增强 if-else 语义清晰度，尤其适用于复杂条件判断或配置驱动场景。
 *   提供三种聚合逻辑函数：全部满足、任一满足、全不满足。
 *
 * Usage:
 *   K_MixedAll(cond1, cond2).then([]{ ... }).otherwise([]{ ... });
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANBOOLUTILS_H
#define BLUEPRINT_VULKANBOOLUTILS_H

#include <cstdint>
#include <utility>

namespace Vulkan::Utils {
    class BoolConditionResult {
        bool result_;

    public:
        constexpr explicit BoolConditionResult(bool result) : result_(result) {}

        template<typename Callback>
        constexpr BoolConditionResult&& then
            (Callback&& cb) && 
        {
            if (result_) {
                std::forward<Callback>(cb)();
            }
            return std::move(*this);
        }

        template<typename Callback>
        constexpr BoolConditionResult&& otherwise
            (Callback&& cb) && 
        {
            if (!result_) {
                std::forward<Callback>(cb)();
            }
            return std::move(*this);
        }

        constexpr explicit operator bool() const { return result_; }
    };

    template<typename... Args>
    constexpr BoolConditionResult K_MixedAll
        (Args&&... args) 
    {
        return BoolConditionResult{(... && static_cast<bool>(args))};
    }

    template<typename... Args>
    constexpr BoolConditionResult K_MixedAny
        (Args&&... args) 
    {
        return BoolConditionResult{(... || static_cast<bool>(args))};
    }

    template<typename... Args>
    constexpr BoolConditionResult K_MixedNone
        (Args&&... args) 
    {
        return BoolConditionResult{!(... || static_cast<bool>(args))};
    }
}

#endif //BLUEPRINT_VULKANBOOLUTILS_H

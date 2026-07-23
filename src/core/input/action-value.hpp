//
// Created by Dean Wilson 23rd July 2026
//

#pragma once

#include "core/input/action-value-type.hpp"
#include "core/math/vector-2d.hpp"
#include <variant>

namespace Core::Input {
using ActionValue = std::variant<bool, float, Core::Math::Vector2D>;

inline ActionValueType ValueTypeOf(const ActionValue& value)
{
  return std::visit(
      [](auto&& v) -> ActionValueType {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, bool>) {
          return ActionValueType::Boolean;
        }
        else if constexpr (std::is_same_v<T, bool>) {
          return ActionValueType::Axis1D;
        }
        else if constexpr (std::is_same_v<T, Core::Math::Vector2D>) {
          return ActionValueType::Axis2D;
        }
        return ActionValueType::Boolean;
      },
      value
  );
}

}  // namespace Core::Input

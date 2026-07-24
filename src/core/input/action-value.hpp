//
// Created by Dean Wilson 23rd July 2026
//

#pragma once

#include "core/utils/zip.hpp"
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
        else if constexpr (std::is_same_v<T, float>) {
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

inline ActionValue Accumulate(const ActionValue& a, const ActionValue& b)
{
  return Zip(
      a,
      b,
      Overloaded{
          [](bool x, bool y) -> ActionValue { return x || y; },
          [](float x, float y) -> ActionValue { return x + y; },
          [](const Core::Math::Vector2D x, const Core::Math::Vector2D y) -> ActionValue {
            return x + y;
          },
      }
  );
};

/*
 * Distance:
 *
 * Measures the deadzone for a given action depending on the ActionValueType
 *
 */
inline float Distance(const ActionValue& a, const ActionValue& b)
{
  return Zip(
      a,
      b,
      Overloaded{
          [](bool x, bool y) -> float { return x != y ? 1.0f : 0.0f; },
          [](float x, float y) -> float { return std::abs(x - y); },
          [](const Core::Math::Vector2D x, const Core::Math::Vector2D y) -> float {
            return (x - y).Length();
          },
      }
  );
};

}  // namespace Core::Input

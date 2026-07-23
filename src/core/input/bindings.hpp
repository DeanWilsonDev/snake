//
// Created by Dean Wilson 23rd July 2026
//

#pragma once

#include "core/input/key-code.hpp"
#include "core/input/key-binding.hpp"
#include "core/math/vector-2d.hpp"

namespace Core::Input::Bindings {

inline KeyBinding Digital(KeyCode key)
{
  return {key, true};
};

inline KeyBinding Axis1D(KeyCode key, float scale)
{
  return {key, scale};
};

inline KeyBinding Axis2D(KeyCode key, Math::Vector2D scale)
{
  return {key, scale};
};

}  // namespace Core::Input::Bindings

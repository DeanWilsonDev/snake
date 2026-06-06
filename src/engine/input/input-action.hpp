//
// Created by Dean Wilson 2nd February 2026
//

#pragma once

#include "core/input/key-code.hpp"

#include <string>
#include <array>

using namespace Core::Input;

namespace Engine {
namespace Input {

enum class Action {
  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,
  Confirm,
  Decline,

  Count,
};

/// Dynamic Actions:
///
/// This setup is overkill but may be something to revisit later
class InputAction {
 public:
  std::string name;
  std::array<KeyCode, 4> keycodes;
  bool isComposite = false;
};

}  // namespace Input

}  // namespace Engine

//
// Created by Dean Wilson 2nd February 2026
//

#pragma once

#include "engine/input/input-action.hpp"
#include "engine/input/key-code.hpp"

#include <array>
#include <cstddef>
#include <vector>
#include "engine/input/input-action.hpp"
#include "engine/input/key-code.hpp"
#include "platform/input/i-input-backend.hpp"

namespace Engine {

namespace Input {

using KeyMap = std::array<std::vector<KeyCode>, static_cast<size_t>(Action::Count)>;

class InputSystem {
 public:
  InputSystem(Platform::Input::IInputBackend& inputBackend);

  void SetKeyMap(const KeyMap& map);
  bool IsActionPressed(const Action action);
  bool IsActionDown(const Action action);
  bool IsActionReleased(const Action action);

 private:
  KeyMap keyMap;
  Platform::Input::IInputBackend& inputBackend;
};
}  // namespace Input

}  // namespace Engine

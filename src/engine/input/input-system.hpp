//
// Created by Dean Wilson 2nd February 2026
//

#pragma once

#include "core/input/key-code.hpp"
#include "core/input/i-input-backend.hpp"
#include "engine/input/input-action.hpp"

#include <array>
#include <cstddef>
#include <vector>

using namespace Core::Input;

namespace Engine {

namespace Input {

using KeyMap = std::array<std::vector<KeyCode>, static_cast<size_t>(Action::Count)>;

class InputSystem {
 public:
  InputSystem(IInputBackend& inputBackend);
  ~InputSystem() = default;
  void SetKeyMap(const KeyMap& map);
  bool IsActionPressed(const Action action) const;
  bool IsActionDown(const Action action) const;
  bool IsActionReleased(const Action action) const;

 private:
  KeyMap keyMap;
  IInputBackend& inputBackend;
};
}  // namespace Input

}  // namespace Engine

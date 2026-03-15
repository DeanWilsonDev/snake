///
/// Created by Dean Wilson 15th March 2026
///

#pragma once

#include "engine/input/key-code.hpp"
#include "engine/input/input-system.hpp"
#include <vector>

using KeyCode = Engine::Input::KeyCode;

namespace Engine::Config {
struct InputConfig {
  Engine::Input::KeyMap keyMap = {};
};

}  // namespace Engine::Config

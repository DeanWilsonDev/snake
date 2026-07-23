///
/// Created by Dean Wilson 15th March 2026
///

#pragma once

#include "core/input/key-map.hpp"
#include "core/input/action.hpp"

namespace Engine::Config {
struct InputConfig {
  Core::Input::KeyMap keyMap = {};
  std::vector<Core::Input::Action> actions = {};
};
}  // namespace Engine::Config

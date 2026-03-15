//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#include "engine/config/input-config.hpp"
#include "engine/config/window-config.hpp"
#include "engine/config/debug-config.hpp"

namespace Engine::Config {

struct EngineConfig {
  WindowConfig window;
  InputConfig input;
  DebugConfig debug;
};
}  // namespace Engine::Config

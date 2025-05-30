//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once
#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H

#include "../../platform/window/config/window-config.h"

namespace Engine::Config {

struct EngineConfig {
  Platform::Config::Window::WindowConfig window;
};
}  // namespace Engine::Config

#endif  // ENGINE_CONFIG_H

//
// Created by Dean Wilson on 15th March 2026
//

#pragma once

#include "engine/config/engine-config.hpp"
#include "engine/config/project-settings.hpp"
#include "engine/config/game-settings.hpp"

namespace Engine::Config {

struct ApplicationConfig {
  EngineConfig engine;
  ProjectSettings project;
  GameSettings game;
};
}  // namespace Engine::Config

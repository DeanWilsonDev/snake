///
/// Created by Dean Wilson 15th March 2026
///

#pragma once

namespace Engine::Config {
struct GameSettings {
  virtual ~GameSettings() = default;
  struct DebugConfig {
    bool enabled;
    bool showDebugLogs;
  } debug;
};

}  // namespace Engine::Config

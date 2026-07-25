///
/// Created by Dean Wilson 15th March 2026
///

#pragma once

namespace Engine::Config {
struct DebugConfig {
  bool enabled = false;
  bool showFPS = false;
  bool showDebugHud = false;
  bool showCoreDebugLogs = false;
  bool showClientDebugLogs = false;
};
}  // namespace Engine::Config

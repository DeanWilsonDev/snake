#pragma once

#include "i-debug-hud.hpp"
#include <memory>

namespace Debug {

class DebugSystem {
 public:
  IDebugHUD& GetActiveDebugHUD();
  void SetActiveDebugHUD(std::shared_ptr<IDebugHUD> hud);
  bool GetDebugMode() const;
  void SetDebugMode(bool enabled);

 private:
  bool debugMode = {true};
  std::shared_ptr<IDebugHUD> activeDebugHUD;
};

extern DebugSystem System;

}  // namespace Debug

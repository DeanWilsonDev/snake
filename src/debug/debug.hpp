#pragma once
#include <utility>
#include <memory>
#include "i-debug-hud.hpp"

namespace Debug {

class DebugSystem {
 public:
  IDebugHUD& GetActiveDebugHUD() const;
  void SetActiveDebugHUD(std::shared_ptr<IDebugHUD> hud);
  bool GetDebugMode() const;
  void SetDebugMode(bool enabled);

 private:
  bool debugMode = {true};
  std::shared_ptr<IDebugHUD> activeDebugHUD;
};

inline DebugSystem System;

inline IDebugHUD& DebugSystem::GetActiveDebugHUD() const
{
  return *this->activeDebugHUD;
}

inline void DebugSystem::SetActiveDebugHUD(std::shared_ptr<IDebugHUD> hud)
{
  this->activeDebugHUD = std::move(hud);
}

inline bool DebugSystem::GetDebugMode() const
{
  return this->debugMode;
};

inline void DebugSystem::SetDebugMode(bool enabled)
{
  this->debugMode = enabled;
}

}  // namespace Debug

// Generic Debug setter
#define UMBRA_DEBUG(...) ::Debug::System.GetActiveDebugHUD().FormatPathAndSet(__VA_ARGS__)

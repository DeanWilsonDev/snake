#include "debug-system.hpp"
#include <utility>
#include <memory>
#include "i-debug-hud.hpp"

namespace Debug {

DebugSystem System;

IDebugHUD& DebugSystem::GetActiveDebugHUD()
{
  return *this->activeDebugHUD;
}

void DebugSystem::SetActiveDebugHUD(std::shared_ptr<IDebugHUD> hud)
{
  this->activeDebugHUD = std::move(hud);
}

bool DebugSystem::GetDebugMode() const
{
  return this->debugMode;
};

void DebugSystem::SetDebugMode(bool enabled)
{
  this->debugMode = enabled;
}

}  // namespace Debug

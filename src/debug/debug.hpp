#pragma once

#include <memory>
#include "debug/i-debug-hud.hpp"

namespace Debug {

IDebugHUD& GetActiveDebugHUD();
void SetActiveDebugHUD(std::shared_ptr<IDebugHUD> hud);
}

#ifdef NDEBUG

// Generic Debug setter
#define UMBRA_DEBUG(path, value) ::Debug::GetActiveDebugHUD().Set((path), (value))

// Type convenience macros
#define UMBRA_DEBUG_STR(path, value) \
  ::Debug::GetActiveDebugHUD().Set((path), ::Debug::DebugValue::FromString(value))

#define UMBRA_DEBUG_NUM(path, value) \
  ::Debug::GetActiveDebugHUD().Set((path), ::Debug::DebugValue::FromNumber(number))

#define UMBRA_DEBUG_BOOL(path, value) \
  ::Debug::GetActiveDebugHUD().Set((path), ::Debug::DebugValue::FromBool(value))

#else

#define UMBRA_DEBUG(path, value) ((void)0)
#define UMBRA_DEBUG_STR(path, value) ((void)0)
#define UMBRA_DEBUG_NUM(path, value) ((void)0)
#define UMBRA_DEBUG_BOOL(path, value) ((void)0)

#endif

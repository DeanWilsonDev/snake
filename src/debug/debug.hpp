#pragma once
#include "debug-system.hpp"

// Generic Debug setter
#define UMBRA_DEBUG(path, value) ::Debug::System.GetActiveDebugHUD().Set((path), (value))

// Type convenience macros
#define UMBRA_DEBUG_STR(path, value) \
  ::Debug::System.GetActiveDebugHUD().Set((path), ::Debug::DebugValue::FromString(value))

#define UMBRA_DEBUG_NUM(path, value) \
  ::Debug::System.GetActiveDebugHUD().Set((path), ::Debug::DebugValue::FromNumber(value))

#define UMBRA_DEBUG_BOOL(path, value) \
  ::Debug::System.GetActiveDebugHUD().Set((path), ::Debug::DebugValue::FromBool(value))

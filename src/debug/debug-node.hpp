#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <variant>
#include <cstddef>
#include "debug-value.hpp"

namespace Debug {

struct DebugNode;
using DebugNodePtr = std::unique_ptr<DebugNode>;
using DebugMap = std::unordered_map<std::string, DebugNodePtr>;

struct DebugNode {
 public:
  std::variant<DebugValue, DebugMap> data;

  bool IsValue() const { return std::holds_alternative<DebugValue>(data); }
  bool IsMap() const { return std::holds_alternative<DebugMap>(data); }

  DebugValue* AsValue() { return IsValue() ? &std::get<DebugValue>(data) : nullptr; }
  DebugMap* AsMap() { return IsMap() ? &std::get<DebugMap>(data) : nullptr; }
};
}  // namespace Debug

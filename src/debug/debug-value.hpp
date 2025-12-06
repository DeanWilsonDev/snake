#pragma once

#include <sstream>
#include <string>
#include <memory.h>

namespace Debug {

struct DebugValue {
  enum class Type { String, Number, Bool };
  Type type;
  std::string stringValue;
  double numberValue;
  bool boolValue;

  static DebugValue FromString(const std::string& value)
  {
    return DebugValue{Type::String, value, 0.0, false};
  }

  static DebugValue FromNumber(const double& value)
  {
    return DebugValue{Type::Number, {}, value, false};
  }

  static DebugValue FromBool(const bool value) { return DebugValue{Type::Bool, {}, 0.0, value}; }

  std::string ToString() const
  {
    switch (this->type) {
      case Type::String:
        return this->stringValue;
      case Type::Number: {
        std::ostringstream ss;
        ss << this->numberValue;
        return ss.str();
      }
      case Type::Bool:
        return this->boolValue ? "true" : "false";
      default:
        return {};
    }
  }
};
}  // namespace Debug

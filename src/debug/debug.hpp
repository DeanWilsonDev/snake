#pragma once

#include <sstream>
#include <string>
#include <unordered_map>
#include <memory.h>
#include <variant>
#include <vector>

struct DebugValue {
  enum class Type { String, Number, Bool };
  Type type;
  std::string stringValue;
  double numberValue;
  bool boolValue;

  static DebugValue FromString(const std::string& value)
  {
    DebugValue debugValue;
    debugValue.type = Type::String;
    debugValue.stringValue = value;
    return debugValue;
  }

  static DebugValue FromBool(const bool& value)
  {
    DebugValue debugValue;
    debugValue.type = Type::Bool;
    debugValue.boolValue = value;
    return debugValue;
  }

  static DebugValue FromNumber(const double& value)
  {
    DebugValue debugValue;
    debugValue.type = Type::Number;
    debugValue.numberValue = value;
    return debugValue;
  }

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
    }
  }
};

struct DebugNode;
using DebugNodePtr = std::unique_ptr<DebugNode>;
using DebugMap = std::unordered_map<std::string, DebugNodePtr>;

struct DebugNode {
 public:
  std::variant<DebugValue, DebugMap> data;

  bool IsValue() const { return std::holds_alternative<DebugValue>(data); }
  bool IsMap() const { return std::holds_alternative<DebugMap>(data); }

  DebugValue* AsValue()
  {
    if (!IsValue()) return nullptr;
    return &std::get<DebugValue>(data);
  }

  DebugMap* AsMap()
  {
    if (!IsMap()) return nullptr;
    return &std::get<DebugMap>(data);
  }

  static DebugNode& GetOrCreateNode(
      std::unordered_map<std::string, DebugNode>& map, const std::string& key
  )
  {
    if (!map.contains(key)) {
      map[key] = std::unordered_map<std::string, DebugNode>{};
    }
    return map[key];
  }

  static DebugNode& GetOrCreatePath(DebugNode& node, const std::vector<std::string>& path)
  {
    std::unordered_map<std::string, DebugNode>* currentMap =
        &std::get<std::unordered_map<std::string, DebugNode>>(node);

    DebugNode* currentNode = &node;

    for (size_t i = 0; i < path.size(); i++) {
      const std::string& key = path[i];

      if (!currentMap->contains(key)) {
        (*currentMap)[key] = std::unordered_map<std::string, DebugNode>{};
      }

      if (i == path.size() - 1) {
        return *currentNode;
      }

      currentMap = &std::get<std::unordered_map<std::string, DebugNode>>(currentNode);
    }
    return *currentNode;
  }
};

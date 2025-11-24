#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include "debug-node.hpp"
#include "debug-value.hpp"

namespace Debug {

class DebugHUD {
 public:
  DebugHUD() = default;

  void AddLine(const std::string& key, const std::string& value);
  void Render();
  void ClearFrameData();

  void Set(const std::string& path, DebugValue value);

  void Remove(const std::string& path);

  void ClearAll();

  void RenderToConsole() const;

 private:
  DebugMap root;

  static std::vector<std::string> SplitPath(const std::string& path);

  DebugNode& GetOrCreateNode(const std::vector<std::string>& parts);

  static void PrintNode(const std::string& key, DebugNode* node, int indent);
};
}  // namespace Debug

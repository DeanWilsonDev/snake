#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <functional>
#include "debug-node.hpp"
#include "debug-value.hpp"
#include "debug/i-debug-hud.hpp"

namespace Debug {

class DebugHUD : public IDebugHUD {
 public:
  DebugHUD();
  ~DebugHUD() override;

  void Visit(
      std::function<void(const std::string& key, const DebugNode& node, int depth)> callback
  ) const override;
  void ClearFrameData() override;

  void Set(const std::string& path, DebugValue value) override;

  void Remove(const std::string& path) override;

  void ClearAll() override;

  void RenderToConsole() const override;

 private:
  DebugMap root;

  static std::vector<std::string> SplitPath(const std::string& path);

  DebugNode& GetOrCreateNode(const std::vector<std::string>& parts);

  void VisitNode(
      const std::string& key, const DebugNode& node, const int depth, auto& callback
  ) const;

  static void PrintNode(const std::string& key, DebugNode* node, int indent);
};
}  // namespace Debug

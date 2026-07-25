#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <functional>
#include "core/debug/debug-node.hpp"
#include "core/debug/debug-value.hpp"
#include "core/debug/i-debug-hud.hpp"

using namespace Core::Debug;

namespace Debug {

class DebugHUD : public Core::Debug::IDebugHUD {
 public:
  DebugHUD(std::string name);
  ~DebugHUD() override;

  void Visit(
      std::function<void(const std::string& key, const DebugNode& node, int depth)> callback
  ) const override;
  void ClearFrameData() override;

  void Set(const std::string_view path, DebugValue value) override;

  void Remove(const std::string& path) override;

  void ClearAll() override;

  void RenderToConsole() const override;

  const std::string& GetName() override;

 private:
  DebugMap root;
  std::string name;

  static std::vector<std::string> SplitPath(const std::string_view path);

  DebugNode& GetOrCreateNode(const std::vector<std::string>& parts);

  void VisitNode(
      const std::string& key, const DebugNode& node, const int depth, auto& callback
  ) const;

  static void PrintNode(const std::string& key, DebugNode* node, int indent);
};

}  // namespace Debug

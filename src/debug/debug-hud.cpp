#include "debug-hud.hpp"
#include "core/debug/debug-node.hpp"
#include "core/debug//debug-value.hpp"

#include <string_view>
#include <functional>
#include <memory>
#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <cstddef>

namespace Debug {

DebugHUD::DebugHUD() {}
DebugHUD::~DebugHUD() {}

void DebugHUD::ClearFrameData() {};

std::vector<std::string> DebugHUD::SplitPath(const std::string_view path)
{
  std::vector<std::string> out;
  std::string current;

  for (char c : path) {
    if (c == '/') {
      if (!current.empty()) {
        out.push_back(current);
        current.clear();
      }
    }
    else {
      current.push_back(c);
    }
  }
  if (!current.empty()) {
    out.push_back(current);
  }
  return out;
}

DebugNode& DebugHUD::GetOrCreateNode(const std::vector<std::string>& parts)
{
  DebugMap* currentMap = &this->root;
  DebugNode* currentNode = nullptr;

  for (std::size_t i = 0; i < parts.size(); ++i) {
    const auto& key = parts[i];

   // Ensure Key exists
    auto it = currentMap->find(key);
    if (it == currentMap->end()) {
      auto node = std::make_unique<DebugNode>();
      node->data = DebugMap{};
      it = currentMap->emplace(key, std::move(node)).first;
    }

    currentNode = it->second.get();

    // Last segment - this is the node the caller wants
    if (i == parts.size() - 1) {
      return *currentNode;
    }

    // Ensure we can descend through maps
    DebugMap* nextMap = currentNode->AsMap();
    if (!nextMap) {
      currentNode->data = DebugMap{};
      nextMap = currentNode->AsMap();
    }
    currentMap = nextMap;
  }

  return *currentNode;  // fallback: should never reach
}

void DebugHUD::Set(const std::string_view path, DebugValue value)
{
  auto parts = SplitPath(path);
  if (parts.empty()) {
    return;
  }

  DebugNode& node = this->GetOrCreateNode(parts);
  node.data = std::move(value);
}

void DebugHUD::Remove(const std::string& path)
{
  auto parts = this->SplitPath(path);
  if (parts.empty()) return;

  DebugMap* current = &this->root;
  std::vector<DebugMap*> stack;
  std::vector<std::string> keys;
  stack.push_back(current);

  for (size_t i = 0; i < parts.size(); ++i) {
    const auto& key = parts[i];

    auto it = current->find(key);
    if (it == current->end()) return;

    if (i == parts.size() - 1) {
      current->erase(it);
      return;
    }

    if (!(it->second->IsMap())) return;

    current = it->second->AsMap();
  }
}

void DebugHUD::ClearAll()
{
  this->root.clear();
}

void DebugHUD::PrintNode(const std::string& key, DebugNode* node, int indent)
{
  std::string pad(indent, ' ');
  if (!node) return;

  if (node->IsValue()) {
    std::cout << pad << key << ": " << node->AsValue()->ToString() << std::endl;
  }
}

void DebugHUD::RenderToConsole() const
{
  for (const auto& [k, nodePtr] : this->root) {
    PrintNode(k, nodePtr.get(), 0);
  }
}

void DebugHUD::Visit(
    std::function<void(const std::string& key, const DebugNode& node, int depth)> callback
) const
{
  for (auto& [key, node] : this->root) {
    this->VisitNode(key, *node, 0, callback);
  }
}

void DebugHUD::VisitNode(
    const std::string& key, const DebugNode& node, const int depth, auto& callback
) const
{
  callback(key, node, depth);

  if (node.IsMap()) {
    for (auto& [childKey, childNode] : *const_cast<DebugNode&>(node).AsMap()) {
      this->VisitNode(childKey, *childNode, depth + 1, callback);
    }
  }
}

}  // namespace Debug

#include "debug-hud.hpp"
#include "debug-node.hpp"
#include "debug-value.hpp"
#include <memory>
#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <cstddef>

namespace Debug {

std::vector<std::string> DebugHUD::SplitPath(const std::string& path)
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

void DebugHUD::Set(const std::string& path, DebugValue value)
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

}  // namespace Debug

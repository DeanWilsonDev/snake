#pragma once

#include "debug.hpp"
#include <string>
#include <vector>
#include <cstddef>
#include <memory>
#include <utility>
#include <iostream>

namespace Debug {
class DebugHUD {
 public:
  DebugHUD() = default;

  void AddLine(const std::string& key, const std::string& value);
  void Render();
  void ClearFrameData();

  void Set(const std::string& path, DebugValue value)
  {
    auto parts = this->SplitPath(path);
    if (parts.empty()) return;

    DebugMap* current = &this->root;

    for (size_t i = 0; i < parts.size(); ++i) {
      const auto& key = parts[i];

      if (i == parts.size() - 1) {
        (*current)[key] = std::make_unique<DebugNode>();
        (*current)[key]->data = std::move(value);
      }
      else {
        auto it = current->find(key);
        if (it == current->end() || !(it->second->IsMap())) {
          (*current)[key] = std::make_unique<DebugNode>();
          (*current)[key]->data = DebugMap{};
        }
        current = (*current)[key]->AsMap();
      }
    }
  }

  void Remove(const std::string& path)
  {
    auto parts = this->SplitPath(path);
    if (parts.empty()) return;

    DebugMap* current = &this->root;
    std::vector<DebugMap*> maps;
    std::vector<std::string> keys;
    maps.push_back(current);

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
      maps.push_back(current);
    }
  }

  void ClearAll() { this->root.clear(); }

  void RenderToConsole() const
  {
    for (const auto& [k, nodePtr] : this->root) {
      PrintNode(k, nodePtr.get(), 0);
    }
  }

 private:
  DebugMap root;

  static std::vector<std::string> SplitPath(const std::string& path)
  {
    std::vector<std::string> out;
    std::string temp;

    for (char c : path) {
      if (c == '/') {
        if (!temp.empty()) {
          out.push_back(temp);
          temp.clear();
        }
      }
      else {
        temp.push_back(c);
      }
    }
    if (!temp.empty()) {
      out.push_back(temp);
    }
    return out;
  }

  static void PrintNode(const std::string& key, const DebugNode* node, int indent)
  {
    std::string pad(indent, ' ');
    if (!node) return;

    if (node->IsValue()) {
      std::cout << pad << key << ": " << node->AsValue()->ToString() << std::endl;
    }
  }
};
}  // namespace Debug

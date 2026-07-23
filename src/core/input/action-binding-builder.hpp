//
// Created by Dean Wilson 23rd July 2026
//

#pragma once

#include "core/input/key-binding.hpp"
#include "core/input/key-code.hpp"
#include "core/math/vector-2d.hpp"
#include <string>
#include <vector>

namespace Core::Input {

class ActionBindingBuilder {
 public:
  explicit ActionBindingBuilder(std::string name);

  ActionBindingBuilder& Digital(std::vector<KeyCode> keys);
  ActionBindingBuilder& Axis1D(std::vector<KeyCode> keys, float scale);
  ActionBindingBuilder& Axis2D(std::vector<KeyCode> keys, Math::Vector2D scale);

  const std::string& Name() const;
  const std::vector<KeyBinding>& Bindings() const;

 private:
  std::string name;
  std::vector<KeyBinding> bindings;
};

inline ActionBindingBuilder Bind(std::string name)
{
  return ActionBindingBuilder(std::move(name));
}
}  // namespace Core::Input

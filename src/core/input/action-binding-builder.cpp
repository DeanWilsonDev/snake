#include "action-binding-builder.hpp"
#include <cassert>
#include <core/logging/log.hpp>
#include "core/math/vector-2d.hpp"

namespace Core::Input {

ActionBindingBuilder::ActionBindingBuilder(std::string name) : name(std::move(name)) {}

ActionBindingBuilder& ActionBindingBuilder::Digital(std::vector<KeyCode> keys)
{
  for (auto key : keys) {
    this->bindings.push_back({key, true});
  }
  return *this;
}

ActionBindingBuilder& ActionBindingBuilder::Axis1D(std::vector<KeyCode> keys, float scale)
{
  for (auto key : keys) {
    this->bindings.push_back({key, scale});
  }
  return *this;
}

ActionBindingBuilder& ActionBindingBuilder::Axis2D(std::vector<KeyCode> keys, Math::Vector2D scale)
{
  for (auto key : keys) {
    this->bindings.push_back({key, scale});
  }
  return *this;
}

const std::string& ActionBindingBuilder::Name() const
{
  return this->name;
}

const std::vector<KeyBinding>& ActionBindingBuilder::Bindings() const
{
  return this->bindings;
}

}  // namespace Core::Input

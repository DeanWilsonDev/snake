//
// Created by Dean Wilson 23rd July 2026
//

#pragma once

#include "core/input/action-binding-builder.hpp"
#include "core/input/action.hpp"
#include "core/input/key-map.hpp"
#include <string>
#include <vector>

namespace Core::Input {

class ActionSet {
 public:
  Core::Input::Action RegisterAction(
      std::string name, ActionValueType type = ActionValueType::Boolean
  );
  const Core::Input::Action& Get(const std::string& name) const;
  const std::vector<Core::Input::Action>& All() const;
  Core::Input::KeyMap BuildKeyMap(std::vector<ActionBindingBuilder> keycodes) const;

 private:
  std::vector<Core::Input::Action> actions;
  int nextId = 0;
};
}  // namespace Core::Input

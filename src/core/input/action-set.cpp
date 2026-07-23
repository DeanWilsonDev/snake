#include "action-set.hpp"
#include <algorithm>
#include <cassert>
#include <core/logging/log.hpp>
#include "core/input/action-binding-builder.hpp"
#include "core/input/action-value-type.hpp"

namespace Core::Input {

Core::Input::Action ActionSet::RegisterAction(
    std::string name, Core::Input::ActionValueType valueType
)
{
  LOG_CORE_INFO("Registering Action: {} with type", name);
  Action action{.id = this->nextId++, .name = std::move(name), .type = valueType};
  this->actions.push_back(action);
  return action;
};

const Core::Input::Action& ActionSet::Get(const std::string& name) const
{
  auto it = std::find_if(this->actions.begin(), this->actions.end(), [&name](const Action& a) {
    return a.name == name;
  });
  assert(it != this->actions.end() && "ActionSet::Get: unregistered action name");
  return *it;
};

const std::vector<Core::Input::Action>& ActionSet::All() const
{
  return this->actions;
};

Core::Input::KeyMap ActionSet::BuildKeyMap(std::vector<ActionBindingBuilder> entries) const
{
  Core::Input::KeyMap keyMap;
  for (auto& entry : entries) {
    const Action& action = this->Get(entry.Name());
    assert(
        std::ranges::all_of(
            entry.Bindings(), [&](auto& b) { return ValueTypeOf(b.contribution) == action.type; }
        ) &&
        "ActionBindingBuilder: contribution type doesn't match RegisterAction's declared type"
    );

    LOG_CORE_INFO("Assigned Action {} with keys", action.name);
    keyMap[action.id] = entry.Bindings();
  }

  return keyMap;
};

}  // namespace Core::Input

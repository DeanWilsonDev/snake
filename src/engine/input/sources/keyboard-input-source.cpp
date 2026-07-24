#include "keyboard-input-source.hpp"
#include <numeric>
#include "core/input/action-value.hpp"
#include "core/input/key-map.hpp"
#include "core/input/i-input-backend.hpp"
#include "core/input/key-binding.hpp"

namespace Engine::Input::Sources {

KeyboardInputSource::KeyboardInputSource(
    Core::Input::IInputBackend& backend, const Core::Input::KeyMap& keyMap
)
    : backend(backend), keyMap(keyMap)
{
}

bool KeyboardInputSource::IsActionDown(Core::Input::Action action) const
{
  auto it = this->keyMap.find(action.id);

  if (it == this->keyMap.end()) {
    return false;
  }

  for (Core::Input::KeyBinding keyBinding : it->second) {
    if (this->backend.IsKeyDown(keyBinding.key)) {
      return true;
    }
  }
  return false;
}

Core::Input::ActionValue KeyboardInputSource::GetActionValue(Core::Input::Action action) const
{
  auto it = this->keyMap.find(action.id);

  if (it == this->keyMap.end()) {
    return {};
  }

  return std::accumulate(
      it->second.begin(),
      it->second.end(),
      Core::Input::ActionValue{},
      [this](Core::Input::ActionValue acc, const Core::Input::KeyBinding& keyBinding) {
        return this->backend.IsKeyDown(keyBinding.key)
                   ? Core::Input::Accumulate(acc, keyBinding.contribution)
                   : acc;
      }
  );
}

void KeyboardInputSource::SetKeyMap(const Core::Input::KeyMap& map)
{
  this->keyMap = map;
}

}  // namespace Engine::Input::Sources

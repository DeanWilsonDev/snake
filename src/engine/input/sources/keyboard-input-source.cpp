#include "keyboard-input-source.hpp"
#include "core/input/key-map.hpp"
#include "core/input/i-input-backend.hpp"
#include "core/input/key-code.hpp"

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

  for (Core::Input::KeyCode keyCode : it->second) {
    if (this->backend.IsKeyDown(keyCode)) {
      return true;
    }
  }
  return false;
}

void KeyboardInputSource::SetKeyMap(const Core::Input::KeyMap& map)
{
  this->keyMap = map;
}

}  // namespace Engine::Input::Sources

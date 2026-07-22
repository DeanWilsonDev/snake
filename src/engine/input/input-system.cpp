#include "engine/input/input-system.hpp"
#include <memory>
#include "core/events/i-event-bus.hpp"
#include "core/input/i-input-backend.hpp"
#include "core/input/key-map.hpp"
#include "engine/input/input-dispatcher.hpp"
#include "engine/input/sources/keyboard-input-source.hpp"

using namespace Core::Input;

namespace Engine::Input {

InputSystem::InputSystem(
    IInputBackend& inputBackend, Core::Events::IEventBus& eventBus, const KeyMap& keyMap
)
    : dispatcher(eventBus)
{
  this->dispatcher.AddSource(
      std::make_unique<Engine::Input::Sources::KeyboardInputSource>(inputBackend, keyMap)
  );
}

void InputSystem::OnUpdate(const float)
{
  this->dispatcher.Run();
}

void InputSystem::OnDebugUpdate() const
{
}

void InputSystem::OnDebugRender() const
{
}

}  // namespace Engine::Input

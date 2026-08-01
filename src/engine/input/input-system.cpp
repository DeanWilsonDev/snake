#include "engine/input/input-system.hpp"
#include <memory>
#include "core/events/i-event-bus.hpp"
#include "core/input/action-router.hpp"
#include "core/input/action-set.hpp"
#include "core/input/i-input-backend.hpp"
#include "core/input/key-map.hpp"
#include "engine/input/input-dispatcher.hpp"
#include "engine/input/sources/keyboard-input-source.hpp"

using namespace Core::Input;

namespace Engine::Input {

InputSystem::InputSystem(
    IInputBackend& inputBackend, Core::Events::IEventBus& eventBus,
    const Core::Input::KeyMap& keyMap, std::vector<Core::Input::Action> actions,
    const Core::Input::ActionSet& actionSet
)
    : dispatcher(eventBus, std::move(actions)), actionRouter(eventBus, actionSet, this->dispatcher)
{
  this->dispatcher.AddSource(
      std::make_unique<Engine::Input::Sources::KeyboardInputSource>(inputBackend, keyMap)
  );
}

void InputSystem::OnUpdate(const float deltaTime)
{
  this->dispatcher.Run();
  this->actionRouter.Update(deltaTime);
}

void InputSystem::OnDebugUpdate() const {}

void InputSystem::OnDebugRender() const {}

Core::Input::ActionRouter& InputSystem::GetActionRouter()
{
  return this->actionRouter;
}

}  // namespace Engine::Input

#include "engine/systems/game-systems/game-system.hpp"
#include "core/events/i-event-bus.hpp"

namespace Engine::Systems {
GameSystem::GameSystem(Core::Events::IEventBus& eventBus) : eventBus(eventBus) {};
void GameSystem::OnUpdate(const float) {};
void GameSystem::OnDebugUpdate() const {};
void GameSystem::OnDebugRender() const {};
void GameSystem::OnRegistration() {};

}  // namespace Engine::Systems

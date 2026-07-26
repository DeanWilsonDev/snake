#include "engine/systems/system.hpp"

namespace Engine::Systems {
System::System() {};
void System::OnUpdate(const float) {};
void System::OnDebugUpdate() const {};
void System::OnDebugRender() const {};
void System::OnRegistration() {};

}  // namespace Engine::Systems

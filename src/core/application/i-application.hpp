//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once

#include "core/debug/i-on-debugable.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/input/action-router.hpp"
#include "core/life-cycle-hooks/i-initialize.hpp"
#include "core/life-cycle-hooks/i-on-updatable.hpp"
#include "core/rendering/i-on-renderable.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "core/scenes/i-scene-manager.hpp"

namespace Core::Input {
class ActionSet;
}  // namespace Core::Input
   //
namespace Core::Input {
class ActionRouter;
}  // namespace Core::Input

namespace Core::Systems {
class ISystem;
}  // namespace Core::Systems

namespace Engine::Config {
struct ApplicationConfig;
}  // namespace Engine::Config

namespace Core {

class IDependencyInjector;

class IApplication : public Core::IInitialize,
                     public Core::Debug::IOnDebugable,
                     public Core::IOnUpdatable,
                     public Core::Rendering::IOnRenderable {
 public:
  virtual ~IApplication() = default;

  virtual void Run() = 0;

 protected:
  // Called once to initialize application-specific systems and resources
  virtual void Configure(Engine::Config::ApplicationConfig& config) = 0;
  virtual void RegisterDependencies() = 0;
  virtual const Engine::Config::ApplicationConfig& GetConfig() const = 0;
  virtual Core::IDependencyInjector& GetInjector() const = 0;
  virtual Core::Scenes::ISceneManager& GetSceneManager() const = 0;
  virtual const Core::Input::ActionSet& GetInputActionSet() const = 0;
  virtual Core::Input::ActionSet& GetInputActionSet() = 0;
  virtual Core::Input::ActionRouter& GetInputActionRouter() = 0;
  virtual Core::Events::IEventBus& GetEventBus() const = 0;
  virtual Core::Rendering::IRenderComponentManager& GetRenderComponentManager() const = 0;
  virtual void RegisterSystem(const std::shared_ptr<Core::Systems::ISystem>& system) = 0;

  virtual void Shutdown() = 0;
};

}  // namespace Core

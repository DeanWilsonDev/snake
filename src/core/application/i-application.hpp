//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once

#include "core/debug/i-on-debugable.hpp"
#include "core/events/i-event-bus.hpp"
#include "core/i-on-updatable.hpp"
#include "core/rendering/i-on-renderable.hpp"
#include "core/rendering/i-render-component-manager.hpp"
#include "core/scenes/i-scene-manager.hpp"
namespace Engine {
namespace Config {
struct ApplicationConfig;
}
}  // namespace Engine

namespace Core {

class IDependencyInjector;

class IApplication : Core::Debug::IOnDebugable, Core::IOnUpdatable, Core::Rendering::IOnRenderable {
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
  virtual Core::Events::IEventBus& GetEventBus() const = 0;
  virtual Core::Rendering::IRenderComponentManager& GetRenderComponentManager() const = 0;

  virtual void Initialize() = 0;

  // Called every frame to handle game-specific logic
  virtual void OnUpdate(float deltaTime) override = 0;
  virtual void OnDebugUpdate() const override = 0;
  void OnRender(const Core::Rendering::IRenderer& renderer) const override = 0;
  virtual void OnDebugRender() const override = 0;
  virtual void Shutdown() = 0;
};

}  // namespace Core

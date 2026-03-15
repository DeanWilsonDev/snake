//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once

namespace Engine {
namespace Config {
struct ApplicationConfig;
}
}  // namespace Engine

namespace Core {

class IDependencyInjector;

class IApplication {
 public:
  virtual ~IApplication() = default;

  virtual void Run() = 0;

 protected:
  // Called once to initialize application-specific systems and resources
  virtual void Configure(Engine::Config::ApplicationConfig& config) = 0;
  virtual void RegisterDependencies(Core::IDependencyInjector& injector) = 0;
  virtual Engine::Config::ApplicationConfig& GetConfig() = 0;

  virtual void Initialize() = 0;

  // Called every frame to handle game-specific logic
  virtual void Update(float deltaTime) = 0;
  virtual void DebugUpdate() = 0;
  virtual void Render() = 0;
  virtual void DebugRender() = 0;
  virtual void Shutdown();
};

}  // namespace Core

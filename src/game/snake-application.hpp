#pragma once
#include "engine/application/application.hpp"
#include "snake-game.hpp"

#include <memory>

namespace Engine {
namespace Config {
struct ApplicationConfig;
}
}  // namespace Engine

namespace Core {
class IDependencyInjector;
namespace Config {
}
}  // namespace Core

namespace Snake {
class SnakeApplication : public Engine::Application {
 public:
  SnakeApplication() : Application(std::make_unique<SnakeGame>()) {};

  virtual void Initialize() override;
  virtual void Configure(Engine::Config::ApplicationConfig& config) override;
  virtual void RegisterDependencies(Core::IDependencyInjector& injector) override;
};
}  // namespace Snake

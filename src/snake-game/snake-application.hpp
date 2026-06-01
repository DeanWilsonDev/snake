#pragma once
#include "engine/application/application.hpp"

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

namespace SnakeGame {
struct SnakeGameSettings;

class SnakeApplication : public Engine::Application {
 public:
  SnakeApplication() : Application() {};

  virtual void Initialize() override;
  virtual void Configure(Engine::Config::ApplicationConfig& config) override;
  virtual void RegisterDependencies() override;
  [[nodiscard]] const SnakeGameSettings& GetSnakeSettings() const;
};

}  // namespace SnakeGame

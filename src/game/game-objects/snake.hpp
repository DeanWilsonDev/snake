#pragma once
#include <deque>
#include <memory>
#include "core/math/vector-2d.hpp"
#include "core/math/transform-2d.hpp"

namespace Core::Components {
class TransformComponent2D;
}
namespace Physics::Components {
class ColliderComponent2D;
}

namespace Renderer2D::Component {
class IRenderComponent2D;
}

namespace Game {
class Apple;

class SnakeSegment;
struct GameSettings;

struct SnakeParams {
  GameSettings& settings;
};

class Snake final {
 public:
  ~Snake();
  explicit Snake(const SnakeParams& snakeParams);

  Snake* Initialize();
  void Update(float deltaTime);
  void Destroy();
  void Move() const;
  void CheckIfShouldGrow();
  void Teleport() const;
  void CreateHead();
  void CreateBody();
  [[nodiscard]] Core::Math::Vector2D GetCenter() const;
  [[nodiscard]] Core::Math::Vector2D GetDirection() { return this->direction; }
  void SetGrow(const bool value) { this->grow = value; }
  void SetActive(bool enabled) const;
  void SetDirection(Core::Math::Vector2D direction);

  [[nodiscard]] GameSettings& GetGameSettings() const { return this->settings; }

  SnakeSegment* head{};
  std::deque<std::unique_ptr<SnakeSegment>> body;

 private:
  GameSettings& settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
  float size = {0};
  float speed = {10};
  int length = {3};
  Core::Math::Vector2D direction{};
  bool grow = false;
  bool debugEnabled = false;
  Core::Math::Transform2D transform = Core::Math::Transform2D::Empty();
};
}  // namespace Game

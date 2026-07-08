#pragma once
#include <deque>
#include "core/math/vector-2d.hpp"
#include "engine/spatial/transform-2d.hpp"

namespace Core::Components {
class TransformComponent2D;
}

namespace Physics::Components {
class ColliderComponent2D;
}

namespace Renderer2D::Component {
class IRenderComponent2D;
}

namespace Core::Entities {
class IEntityManager;
}

namespace SnakeGame {
class SnakeSegment;
}

namespace SnakeGame {
class SnakeSegmentParams;
}

namespace SnakeGame {
struct SnakeGameSettings;

}

namespace SnakeGame {
class Apple;
}

namespace SnakeGame {

struct SnakeParams {
  Core::Entities::IEntityManager& entityManager;
  const SnakeGameSettings& settings;
  int screenWidth;
  int screenHeight;
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
  void CreateSegment(SnakeSegmentParams params);
  void Teleport() const;
  void CreateHead();
  void CreateBody();
  [[nodiscard]] Core::Math::Vector2D GetCenter() const;
  [[nodiscard]] Core::Math::Vector2D GetDirection() { return this->direction; }
  void SetGrow(const bool value) { this->grow = value; }
  void SetActive(bool enabled) const;
  void SetDirection(Core::Math::Vector2D direction);

  [[nodiscard]] const SnakeGameSettings& GetSnakeGameSettings() const { return this->settings; }

  SnakeSegment* head{};
  std::deque<SnakeSegment*> body;

 private:
  Core::Entities::IEntityManager& entityManager;
  const SnakeGameSettings& settings;
  int screenWidth;
  int screenHeight;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
  float size = {0};
  float speed = {10};
  int length = {3};
  Core::Math::Vector2D direction{};
  bool grow = false;
  bool debugEnabled = false;
  Engine::Spatial::Transform2D transform = Engine::Spatial::Transform2D::Empty();
};
}  // namespace SnakeGame

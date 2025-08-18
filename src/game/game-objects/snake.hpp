#pragma once

#include "core/entity.h"
#include <deque>

namespace Platform::Input {
class IInput;
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

/**
 * @struct SnakeParams
 * @brief A structure holding the parameters required to initialize a Snake object.
 *
 * This structure encapsulates references to essential components and settings
 * required for the Snake's functionalities, including rendering, physics, and
 * general game settings.
 *
 * @note The contained references must remain valid for the lifetime of any Snake
 *       instance that depends on them.
 *
 * @param renderComponent A reference to the 2D rendering component that is utilized by the Snake
 * for rendering.
 * @param colliderComponent A reference to the 2D collider component that handles the Snake's
 * physical interactions within the game world.
 * @param settings A reference to the game settings that influence the Snake's behavior and
 * configuration.
 */
struct SnakeParams {
  Renderer2D::Component::IRenderComponent2D& renderComponent;
  Physics::Components::ColliderComponent2D& colliderComponent;
  Platform::Input::IInput& input;
  GameSettings& settings;
};

/**
 * @class Snake
 * @brief Represents the snake entity within the game.
 *
 * The Snake class manages the behaviors, state, and interactions of the snake
 * within the game. It handles movement, growth, collision, and rendering operations.
 *
 * This is the main class responsible for encapsulating all functionality related
 * to the snake, relying on external parameters provided through the SnakeParams
 * structure for initialization.
 *
 * @note The contained references to components must remain valid during the
 * lifetime of the Snake instance.
 */
class Snake final : public Core::Entity {
 public:
  ~Snake() override;
  explicit Snake(const SnakeParams& snakeParams);

  Snake* Initialize();
  void Update(float deltaTime) override;
  void Destroy();
  void Move() const;
  void CheckIfShouldGrow();
  void Teleport() const;
  [[nodiscard]] Core::Math::Vector2D GetCenter() const;
  void SetGrow(const bool value) { this->grow = value; }

  // Getters
  [[nodiscard]] Physics::Components::ColliderComponent2D& GetColliderComponent() const
  {
    return this->colliderComponent;
  }
  [[nodiscard]] Renderer2D::Component::IRenderComponent2D& GetRendererComponent2D() const
  {
    return this->renderComponent;
  }


  SnakeSegment* head{};
  std::deque<SnakeSegment*> body;

 private:
  Renderer2D::Component::IRenderComponent2D& renderComponent;
  Physics::Components::ColliderComponent2D& colliderComponent;
  Platform::Input::IInput& input;
  GameSettings& settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
  float size = {0};
  float speed = {10};
  int length = {3};
  Core::Math::Vector2D direction{};
  bool grow = false;
  bool debugEnabled = false;
};
}  // namespace Game

#pragma once

#include "core/entity.h"
#include "game-settings.h"
#include "game-session.h"
#include "snake-body.h"
#include <deque>
#include "raylib.h"

class GameState;

struct SnakeParams {
  GameSettings& settings;
  Component::IRenderable& renderComponent;
};

class Snake final : Core::Entity {
 public:
  virtual ~Snake();
  explicit Snake(const SnakeParams& snakeParams);

  void Update() override;
  void Destroy();
  void Move();
  void CheckIfShouldGrow();
  void Teleport() const;

  float size;
  float speed;
  int length;
  Vector2 direction;
  SnakeBody* head;
  std::deque<SnakeBody*> body;
  bool grow = false;

 private:
  GameSettings settings;
  float accumulatedDistance = 0.0f;
  bool directionChanged = false;
};

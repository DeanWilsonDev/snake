//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include <memory>
#include "entity.h"
#include "core/components/transform-component-2d.hpp"
#include "core/math/i-transform-2d.hpp"

namespace Core::Components {
class IComponent;
}

namespace Core::Entity {

struct GameEntityParams : EntityParams {
  Core::Math::ITransform2D* transform = {nullptr};

  GameEntityParams(Core::Math::ITransform2D* transform = nullptr, bool active = true)
      : EntityParams(active), transform(transform)
  {
  }
};

class GameEntity : public Entity {
 public:
  explicit GameEntity(const GameEntityParams& params);

  GameEntity(const GameEntity&) = delete;
  GameEntity& operator=(const GameEntity&) = delete;

  GameEntity(GameEntity&&) noexcept = delete;
  GameEntity& operator=(GameEntity&&) noexcept = delete;

  ~GameEntity() override;

  void Update(float deltaTime) override;
  void Initialize() override;
  Components::TransformComponent2D& GetTransformComponent() { return *this->transformComponent; }

  // Properties
 protected:
  std::unique_ptr<Components::TransformComponent2D> transformComponent{nullptr};
};
}  // namespace Core::Entity

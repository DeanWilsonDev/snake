//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include <memory>
#include "core/entity/i-game-entity.hpp"
#include "entity-base.hpp"
#include "core/components/transform-component-2d.hpp"
#include "core/math/i-transform-2d.hpp"

namespace Core::Components {
class IComponent;
}

namespace Engine::Entity {

struct GameEntityParams : EntityBaseParams {
  Core::Math::ITransform2D* transform = {nullptr};

  GameEntityParams(Core::Math::ITransform2D* transform = nullptr, bool active = true)
      : EntityBaseParams(active), transform(transform)
  {
  }
};

class GameEntity : public EntityBase, Core::Entity::IGameEntity {
 public:
  explicit GameEntity(const GameEntityParams& params);

  GameEntity(const GameEntity&) = delete;
  GameEntity& operator=(const GameEntity&) = delete;

  GameEntity(GameEntity&&) noexcept = delete;
  GameEntity& operator=(GameEntity&&) noexcept = delete;

  ~GameEntity() override;

  virtual void Update(float deltaTime) override;
  virtual void DebugUpdate() override;
  virtual void Initialize() override;
  virtual Core::Components::TransformComponent2D& GetTransformComponent() override;

  // Properties
 protected:
  std::unique_ptr<Core::Components::TransformComponent2D> transformComponent{nullptr};
};
}  // namespace Engine::Entity

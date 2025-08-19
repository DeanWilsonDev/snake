//
// Created by Dean Wilson on 29/5/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "math/transform-2d.hpp"

namespace Renderer2D {
class IRenderable;
namespace Component {
class IRenderComponent2D;
}
}  // namespace Renderer2D

namespace Core {
class Entity {
 public:
  explicit Entity();
  virtual ~Entity() = 0;

  virtual void Update(float deltaTime);
  virtual void SetEnabled(const bool enabled) { this->enabled = enabled; }

  // Properties
 public:
  Math::Transform2D transform = {Math::Transform2D::Empty()};

 private:
  bool enabled{false};
};
}  // namespace Core
#endif  // ENTITY_H

//
// Created by Dean Wilson on 29/5/2025.
//

#ifndef ENTITY_H
#define ENTITY_H

namespace Component {
class IRenderable;
}

namespace Core {
class Entity {
 public:
  explicit Entity(Component::IRenderable* renderComponent);
  virtual ~Entity() = 0;

  virtual void Update();
  [[nodiscard]] Component::IRenderable* GetRenderComponent() const;

 protected:
  Component::IRenderable* renderComponent;
};
}  // namespace Core
#endif  // ENTITY_H

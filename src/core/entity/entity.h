//
// Created by Dean Wilson on 29/5/2025.
//
#pragma once

#include "core/math/transform-2d.hpp"

namespace Core::Entity {
class Entity {
 public:
  explicit Entity(int id);
  virtual ~Entity() = 0;

  virtual void Initialize();
  virtual void Update(float deltaTime);
  [[nodiscard]] int GetID() const;

private:
  int id{};

};
}  // namespace Core::Entity

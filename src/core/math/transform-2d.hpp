//
// Created by Dean Wilson on 1/6/2025.
//

#pragma once
#include "vector-2d.hpp"

namespace Core {
class Transform2D {

  Transform2D(Math::Vector2D position, Math::Vector2D rotation, Math::Vector2D scale);
  ~Transform2D() = default;

  Math::Vector2D position;
  Math::Vector2D rotation;
  Math::Vector2D scale;
};
}


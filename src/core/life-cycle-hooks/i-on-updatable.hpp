//
// Created by Dean Wilson 22th March 2026
//

#pragma once

namespace Core {

class IOnUpdatable {
 public:
  virtual ~IOnUpdatable() = default;
  virtual void OnUpdate(const float deltaTime) = 0;
};

}  // namespace Core

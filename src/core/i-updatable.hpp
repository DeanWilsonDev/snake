//
// Created by Dean Wilson 28th February 2026
//

#pragma once

namespace Core {

class IUpdatable {
 public:
  virtual ~IUpdatable() = default;
  virtual void Update(float deltaTime) = 0;
};

}  // namespace Core

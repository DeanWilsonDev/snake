//
// Created by Dean Wilson 28th February 2026
//

#pragma once

namespace Core {

class IUpdatable {
 public:
  virtual ~IUpdatable() = default;
  [[maybe_unused]] virtual void Update([[maybe_unused]] float deltaTime) {};
};

}  // namespace Core

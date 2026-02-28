//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once

#include "core/i-debugable.hpp"

namespace Core {

class IGame: public IDebugable {
public:
  virtual ~IGame() = default;

  // Called once to initialize game-specific systems and resources
  virtual void Initialize() = 0;

  // Called every frame to handle game-specific logic
  virtual void Update([[maybe_unused]] float deltaTime)=0;
  [[maybe_unused]] virtual void DebugUpdate() = 0; 

  // Called every frame to handle game-specific rendering
  virtual void Render() = 0;
};

} // Core

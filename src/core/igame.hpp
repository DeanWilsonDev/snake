//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once

namespace Core {

class IGame {
public:
  virtual ~IGame() = default;

  // Called once to initialize game-specific systems and resources
  virtual void Initialize() = 0;

  // Called every frame to handle game-specific logic
  virtual void Update(float deltaTime)=0;

  // Called every frame to handle game-specific rendering
  virtual void Render() = 0;
};

} // Core

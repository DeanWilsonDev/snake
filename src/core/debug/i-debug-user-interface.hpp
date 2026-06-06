//
// Created by Dean Wilson on 6th June 2026
//

#pragma once

namespace Core {
namespace Math {
struct Vector2D;
}
namespace Debug {
class IDebugHUD;

class IDebugUserInterface {
 public:
  virtual ~IDebugUserInterface() = default;
  virtual void RenderDebugHUD(const Core::Debug::IDebugHUD& debugHUD) = 0;
};
}  // namespace Debug
}  // namespace Core

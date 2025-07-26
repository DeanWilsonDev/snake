#pragma once

namespace Core::Math {
struct Vector2D;
}

namespace UserInterface {

class IUserInterface {
 public:
  virtual ~IUserInterface() = default;
  virtual void DrawTextCentered(const char* text, Core::Math::Vector2D position, float fontSize) = 0;
};
}  // namespace UserInterface

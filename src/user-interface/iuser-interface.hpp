#pragma once

namespace Core::Math {
struct Vector2D;
}

namespace UserInterface {

class IUserInterface {
 public:
  virtual ~IUserInterface() = default;
  virtual void Render() = 0;
  static void DrawTextCentered(const char* text, Core::Math::Vector2D position, float fontSize);
};
}  // namespace UserInterface

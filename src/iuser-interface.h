#pragma once

class Vector2;

class IUserInterface {
 public:
  virtual ~IUserInterface() = default;

  virtual void drawTextCentered(const char* text, Vector2 position, float fontSize) = 0;
};

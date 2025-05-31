#pragma once

class Vector2;

namespace Core {

class IUserInterface {
 public:
  virtual ~IUserInterface() = default;
  virtual void Render() = 0;
};
}  // namespace Core

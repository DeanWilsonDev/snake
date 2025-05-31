#pragma once
#include "key-codes.hpp"

namespace Platform::Input {

class IInput {
 public:
  virtual ~IInput() = default;
  virtual bool IsKeyDown(KeyCode keyCode) = 0;
  virtual bool IsKeyPressed(KeyCode keyCode) = 0;
};
}  // namespace Platform::Input
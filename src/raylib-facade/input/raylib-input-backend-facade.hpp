//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once

#include "core/input/i-input-backend.hpp"
#include "core/input/key-code.hpp"

using namespace Core::Input;

namespace RaylibFacade::Input {
class RaylibInputBackendFacade final : public IInputBackend {
 public:
  RaylibInputBackendFacade();
  ~RaylibInputBackendFacade() override = default;
  bool IsKeyPressed(KeyCode keyCode) override;
  bool IsKeyDown(KeyCode keyCode) override;
  bool IsKeyReleased(KeyCode keyCode) override;

 private:
  static int MapKeyCode(KeyCode keyCode);
};

}  // namespace RaylibFacade::Input

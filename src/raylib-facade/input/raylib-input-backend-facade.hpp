//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once

#include "platform/input/i-input-backend.hpp"
#include "engine/input/key-code.hpp"

namespace RaylibFacade::Input {
class RaylibInputBackendFacade final : public Platform::Input::IInputBackend {
 public:
  RaylibInputBackendFacade();
  ~RaylibInputBackendFacade() override = default;
  bool IsKeyPressed(Engine::Input::KeyCode keyCode) override;
  bool IsKeyDown(Engine::Input::KeyCode keyCode) override;
  bool IsKeyReleased(Engine::Input::KeyCode keyCode) override;

 private:
  static int MapKeyCode(Platform::Input::KeyCode keyCode);
};

}  // namespace RaylibFacade::Input

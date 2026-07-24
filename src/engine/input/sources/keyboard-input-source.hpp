//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once

#include "core/input/i-input-backend.hpp"
#include "core/input/i-input-source.hpp"
#include "core/input/key-map.hpp"

namespace Engine::Input::Sources {
class KeyboardInputSource final : public Core::Input::IInputSource {
 public:
  KeyboardInputSource(Core::Input::IInputBackend& backend, const Core::Input::KeyMap& keyMap);
  bool IsActionDown(Core::Input::Action action) const override;
  virtual Core::Input::ActionValue GetActionValue(Core::Input::Action action) const override;
  void SetKeyMap(const Core::Input::KeyMap& map);

 private:
  Core::Input::IInputBackend& backend;
  Core::Input::KeyMap keyMap;
};
}  // namespace Engine::Input::Sources

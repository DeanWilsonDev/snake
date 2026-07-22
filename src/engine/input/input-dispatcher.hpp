//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once

#include <memory>
#include <vector>
#include "core/input/i-input-dispatcher.hpp"

namespace Core::Input {
class IInputSource;
}

namespace Core::Events {
class IEventBus;
}

namespace Engine::Input {
class InputDispatcher final : public Core::Input::IInputDispatcher {
 public:
  InputDispatcher(Core::Events::IEventBus& eventBus);
  virtual void AddSource(std::unique_ptr<Core::Input::IInputSource> source) override;
  virtual void Run() override;
  bool IsActionDown(Core::Input::Action action) const;

 private:
  std::vector<std::unique_ptr<Core::Input::IInputSource>> sources;
  std::array<bool, static_cast<size_t>(Core::Input::Action::Count)> lastFrameDown = {};
  std::array<bool, static_cast<size_t>(Core::Input::Action::Count)> currentDown = {};
  Core::Events::IEventBus& eventBus;
};
}  // namespace Engine::Input

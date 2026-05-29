#pragma once
#include <functional>
#include <string>

namespace Core {
namespace Scenes {
struct SceneTransitionContext {
  std::function<void(const std::string&)> SwitchTo;
  std::function<void(const std::string&)> Push;
  std::function<void()> Pop;
};
}  // namespace Scenes
}  // namespace Core

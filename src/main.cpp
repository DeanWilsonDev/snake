#include "engine/application.h"
#include "raylib/window/raylib-window-adapter.hpp"
#include "game-session.h"
#include "log.h"
#include "core.h"
#include "platform/input/input-manager.hpp"
#include "platform/window/window-manager.hpp"
#include "raylib/input/raylib-input-adapter.hpp"

class IWindow;

int main(int argc, char* argv[])
{
  // Initialize Logging
  Umbra::Logging::Log::init(DEBUG_ENABLED);
  LOG_DEBUG("Debug Log Working {}", 1);
  LOG_WARNING("Warning Log Working {}", 2);
  LOG_CORE_ERROR("Core Logging Working {}", 3);

  auto raylibInput = std::make_unique<RaylibAdapter::Input::RaylibInputAdapter>();
  Platform::Input::InputManager::SetBackend(std::move(raylibInput));

  auto raylibWindow = std::make_unique<RaylibAdapter::Window::RaylibWindowAdapter>();
  Platform::Window::WindowManager::SetBackend(std::move(raylibWindow));

  /*
   * TODO: Hook all this backup once all adapters have been refactored
   */

  // IRenderer* renderer = new RaylibAdapter::Renderer::RaylibRenderer();
  // IUserInterface* ui = new RaylibAdapter::UserInterface::RaylibUI();
  //
  // const Engine::ApplicationParams applicationParams = {
  //     .renderer = renderer,
  //     .ui = ui,
  // };

  // Engine::Application* application = new Engine::Application(applicationParams);

  // application->Run();
  return 0;
};

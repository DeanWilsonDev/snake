#include "engine/application.h"
#include "core/iuser-interface.h"
#include "raylib/renderer/raylib-renderer.h"
#include "raylib/user-interface/raylib-ui.h"
#include "raylib/window/raylib-window.h"
#include "game-session.h"
#include "log.h"
#include "core.h"
#include "platform/input/iinput.hpp"
#include "platform/input/input-manager.hpp"
#include "raylib/input/raylib-input.hpp"

class IWindow;

int main(int argc, char* argv[])
{
  // Initialize Logging
  Umbra::Logging::Log::init(DEBUG_ENABLED);
  LOG_DEBUG("Debug Log Working {}", 1);
  LOG_WARNING("Warning Log Working {}", 2);
  LOG_CORE_ERROR("Core Logging Working {}", 3);

  auto raylibInput = std::unique_ptr<RaylibAdapter::Input::RaylibInput>();
  Platform::Input::InputManager::SetBackend(std::move(raylibInput));


  // TODO: Hook all this backup once everything is connected properly
  // IWindow* window = new RaylibAdapter::Window::RaylibWindow();
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

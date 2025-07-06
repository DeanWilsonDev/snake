#include "engine/application.h"
#include "raylib-facade/window/raylib-window-facade.hpp"
#include "game-session.h"
#include "log.h"
#include "core.h"
#include "platform/input/input-manager.hpp"
#include "platform/window/window-manager.hpp"
#include "raylib-facade/input/raylib-input-facade.hpp"
#include "raylib-facade/renderer/raylib-renderer-facade.hpp"
#include "raylib-facade/user-interface/raylib-user-interface-facade.hpp"
#include "user-interface/user-interface-manager.hpp"


class IWindow;

int main(int argc, char* argv[])
{
  // Initialize Logging
  constexpr bool debugEnabled = DEBUG_ENABLED;
  Umbra::Logging::Log::init(debugEnabled);
  LOG_DEBUG("Debug Log Working {}", 1);
  LOG_WARNING("Warning Log Working {}", 2);
  LOG_CORE_ERROR("Core Logging Working {}", 3);

  // Main Quest: [Main] Move dependencies to the application class
  // Side Quest: [DependencyInjector] Create a Dependency Injector Class to handle Dependecies

  Platform::Input::InputManager::SetBackend(std::make_unique<RaylibFacade::Input::RaylibInputFacade>());
  Platform::Window::WindowManager::SetBackend(std::make_unique<RaylibFacade::Window::RaylibWindowFacade>());
  UserInterface::UserInterfaceManager::SetBackend(std::make_unique<RaylibFacade::UserInterface::RaylibUserInterfaceFacade>());


  /*
   * Main Quest: [Main] Finish hooking up the application in the main file
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

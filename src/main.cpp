#include "engine/entry-point.hpp"  // NOLINT(misc-include-cleaner)
#include "game/snake-application.hpp"

Engine::Application* CreateApplication()  // NOLINT(misc-include-cleaner)
{
  return new Snake::SnakeApplication();
};

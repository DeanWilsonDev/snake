#include "engine/entry-point.hpp"
#include "snake-game/snake-application.hpp"

Core::IApplication* CreateApplication()
{
  return new SnakeGame::SnakeApplication();
};

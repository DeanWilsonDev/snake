#include "engine/entry-point.hpp"  
#include "game/snake-application.hpp"

Core::IApplication* CreateApplication()  
{
  return new Snake::SnakeApplication();
};

#include "engine/entry-point.hpp"  
#include "game/snake-application.hpp"

Engine::Application* CreateApplication()  
{
  return new Snake::SnakeApplication();
};

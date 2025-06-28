//
// Created by Dean Wilson on 28/6/2025.
//

#include "raylib-core-facade.hpp"
#include "raylib.h"

int RaylibFacade::Core::RaylibCoreFacade::GetRandomValue(const int min, const int max)
{
  return ::GetRandomValue(min, max);
}

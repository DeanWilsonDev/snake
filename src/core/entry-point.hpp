#pragma once

#include "core/i-application.hpp"

extern Core::IApplication* CreateApplication();

int main()
{
  auto app = CreateApplication();
  app->Run();
  delete app;
  return 0;
}

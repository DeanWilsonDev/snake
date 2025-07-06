//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once
#include "core/implementation-manager.hpp"

namespace Platform::Window {
class IWindow;
}
namespace Platform::Window {

class WindowManager final: public Core::ImplementationManager<IWindow>{
public:
  WindowManager();
  static int GetScreenHeight();
  static int GetScreenWidth();
};
}

//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once
#include <memory>

namespace Platform::Window {
class IWindow;
}
namespace Platform::Window {

class WindowManager {
public:
  WindowManager();
  static void SetBackend(std::unique_ptr<IWindow> windowImpl);
  static int GetScreenHeight();
  static int GetScreenWidth();

private:
  static bool IsInitialized();
  static std::unique_ptr<IWindow> backend;
};

}

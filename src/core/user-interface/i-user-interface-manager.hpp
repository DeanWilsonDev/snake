//
// Created by Dean Wilson on 15th March 2026
//

#pragma once

#include "core/debug/i-debugable.hpp"
#include "core/rendering/i-render-manager.hpp"
#include "core/i-updatable.hpp"

namespace Core {
namespace UserInterface {
class IUserInterfaceManager : public IUpdatable, Debug::IDebugable, Rendering::IRenderManager {
 public:
  virtual ~IUserInterfaceManager() = default;

  void DrawUI() const;
  void DebugDrawUI() const;
};
}  // namespace UserInterface
}  // namespace Core

//
// Created by Dean Wilson on 15th March 2026
//

#pragma once

#include "core/debug/i-on-debugable.hpp"
#include "core/rendering/i-on-renderable.hpp"
#include "core/i-on-updatable.hpp"



// MAIN QUEST: Refactor this and the concrete class (Move the concrete class to Engine)
namespace Core {
namespace UserInterface {
class IUserInterfaceManager : public IOnUpdatable, Debug::IOnDebugable, Rendering::IOnRenderable {
 public:
  virtual ~IUserInterfaceManager() = default;

  void DrawUI() const;
  void DebugDrawUI() const;
};
}  // namespace UserInterface
}  // namespace Core

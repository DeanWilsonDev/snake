//
// Created by Dean Wilson on 6/7/2025.
//

#pragma once
#include "core/implementation-manager.hpp"

namespace Core::Math {
struct Vector2D;
}
namespace UserInterface {

class IUserInterface;

class UserInterfaceManager final : public Core::ImplementationManager<IUserInterface>{
public:
  UserInterfaceManager();
  static void DrawTextCentered(const char* text, Core::Math::Vector2D position, float fontSize);
};
} // UserInterface

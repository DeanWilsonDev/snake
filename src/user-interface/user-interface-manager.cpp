//
// Created by Dean Wilson on 6/7/2025.
//

#include "user-interface-manager.hpp"

#include "iuser-interface.hpp"
#include "core/math/vector-2d.hpp"

namespace UserInterface {

UserInterfaceManager::UserInterfaceManager() {}

void UserInterfaceManager::DrawTextCentered(
    const char* text, const Core::Math::Vector2D position, const float fontSize
)
{
  if (IsInitialized()) {
    return;
  }
  GetBackend()->DrawTextCentered(text, position, fontSize);
}

}  // namespace UserInterface
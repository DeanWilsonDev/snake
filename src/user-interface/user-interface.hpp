//
// Created by Dean Wilson on 12/7/2025.
//

#pragma once
#include "user-interface-manager.hpp"
#include "core/math/vector-2d.hpp"

namespace UserInterface {

class UserInterface {
 public:

  /**
   * Renders a text string centered at the specified position on the screen with the given font
   * size.
   *
   * @param text The text string to be rendered.
   * @param position The 2D position where the text should be drawn, specified in screen
   * coordinates.
   * @param fontSize The size of the font to be used for rendering the text.
   */
  static void DrawTextCentered(
      const char* text, const Core::Math::Vector2D position, const float fontSize
  )
  {
    return UserInterfaceManager::DrawTextCentered(text, position, fontSize);
  }
};

}  // namespace UserInterface

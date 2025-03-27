#pragma once
#include "iuser-interface.h"

class Vector2;

class RaylibUI : public IUserInterface {
  void drawTextCentered(const char* text, Vector2 position, float fontSize) override;
};

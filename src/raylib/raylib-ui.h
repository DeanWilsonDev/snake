#pragma once
#include "../core/iuser-interface.h"
#include "log.h"

class Vector2;

class RaylibUI : public IUserInterface {
 public:
  RaylibUI() { LOG_TRACE("Initializing User Interface"); };
  void DrawTextCentered(const char* text, Vector2 position, float fontSize) override;
};

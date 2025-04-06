#pragma once

#include "game-settings.h"
#include "game-session.h"
#include "igame-state.h"
#include "iuser-interface.h"

class IGameContext {
 public:
  virtual ~IGameContext() = default;
  virtual void changeState(IGameState* newState) = 0;
  virtual GameSettings& getSettings() = 0;
  virtual GameSession& getGameSession() = 0;
  virtual IUserInterface& getUI() = 0;
};

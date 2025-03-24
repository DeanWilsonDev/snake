#include <MacTypes.h>
#include "raylib.h"
#include <cstdio>
#include "snake.h"
#include "apple.h"
#include "game-state.h"
#include "user-interface.h"

int main(int argc, char* argv[])
{
  GameState* gameState = new GameState();

  char scoreBuffer[100] = {0};

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(DEFAULT_TARGET_FPS);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (gameState->getState()) {
      case STATE_MAIN_MENU:
        UserInterface::DrawTextCentered("Snake", (Vector2){SCREEN_WIDTH / 2.0f, 40.0f}, 80);
        UserInterface::DrawTextCentered(
            "Press 'Enter' to start", (Vector2){SCREEN_WIDTH / 2.0f, 200.0f}, 20
        );
        if (IsKeyPressed(KEY_ENTER)) {
          gameState->setState(STATE_GAMEPLAY);
        }
        break;
      case STATE_GAMEPLAY:
        std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", gameState->getScore());
        UserInterface::DrawTextCentered(scoreBuffer, (Vector2){80, 30}, 20);

        gameState->update();
        break;
      case STATE_GAME_OVER:

        UserInterface::DrawTextCentered("Game Over", (Vector2){SCREEN_WIDTH / 2.0f - 40, 40}, 80);
        UserInterface::DrawTextCentered(
            "Press 'Enter' to start", (Vector2){SCREEN_WIDTH / 2.0f, 200.0f}, 20
        );

        std::snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %d", gameState->getScore());
        UserInterface::DrawTextCentered(scoreBuffer, (Vector2){SCREEN_WIDTH / 2.0f, 150.0f}, 20);

        if (IsKeyPressed(KEY_ENTER)) {
          delete gameState;
          gameState = new GameState();
          gameState->setState(STATE_GAMEPLAY);
        }
        break;
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
};

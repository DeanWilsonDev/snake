#pragma once
#include "game-settings.h"
#include "irenderer.h"

class Color;

class RaylibRenderer : public IRenderer {
 public:
  RaylibRenderer(GameSettings settings);
  ~RaylibRenderer() = default;

  void beginDrawing() override;
  void stopDrawing() override;
  void clearBackground(Color color) override;
  void draw() override;

 private:
  GameSettings settings;
};

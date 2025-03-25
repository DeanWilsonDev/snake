#pragma once
class Color;

class IRenderer {
 public:
  virtual ~IRenderer() = default;

  void virtual beginDrawing() = 0;
  void virtual clearBackground(Color color) = 0;
  void virtual stopDrawing() = 0;
  void virtual draw() = 0;
};

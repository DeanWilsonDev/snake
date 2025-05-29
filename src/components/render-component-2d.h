#pragma once

#ifndef RENDERER_H
#define RENDERER_H
#include "../render-2d/irenderable.h"
#include "../core/types.h"

class IRenderer;
class IStateMachine;

namespace Component {

class RenderComponent2D final : public Render2D::IRenderable {
 public:
  RenderComponent2D(float width, float height, float positionX, float positionY, Core::Color color);
  ~RenderComponent2D() override;
  void Render(IRenderer& renderer) const override;
  void SetPosition(float x, float y) override;
  [[nodiscard]] float GetX() const override;
  [[nodiscard]] float GetY() const override;
  [[nodiscard]] float GetWidth() const override;
  [[nodiscard]] float GetHeight() const override;

 private:
  float width;
  float height;
  float positionX;
  float positionY;
  Core::Color color;
};
}  // namespace Component

#endif  // RENDERER_H

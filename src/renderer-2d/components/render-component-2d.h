#pragma once

#include "renderer-2d/components/i-render-component-2d.h"
#include "core/color.h"
#include "core/math/size-2d.hpp"
#include "core/math/vector-2d.hpp"

namespace Renderer2D {
class IRenderer;
}

namespace Renderer2D::Component {

class RenderComponent2D final : public IRenderComponent2D {
 public:
  RenderComponent2D(float positionX, float positionY, float width, float height, Core::Color color);
  RenderComponent2D(Core::Math::Vector2D position, Core::Math::Size2D size, Core::Color color);
  ~RenderComponent2D() override = default;
  void Render(IRenderer& renderer) const override;
  void SetPosition(float x, float y) override;
  [[nodiscard]] float GetX() const override;
  [[nodiscard]] float GetY() const override;
  [[nodiscard]] float GetWidth() const override;
  [[nodiscard]] float GetHeight() const override;

 private:
  Core::Math::Vector2D position;
  Core::Math::Size2D size;
  Core::Color color;
};
}  // namespace Renderer2D::Component
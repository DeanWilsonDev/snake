#pragma once

#include "renderer-2d/components/i-render-component-2d.hpp"
#include "core/color.hpp"

namespace Core::Math {
class ITransform2D;
}
namespace Renderer2D {
class IRenderer;
}

namespace Renderer2D::Component {

class RenderComponent2D final : public IRenderComponent2D {
 public:
  RenderComponent2D(Core::Math::ITransform2D& transform, Core::Color color, bool& active);
  ~RenderComponent2D() override = default;
  void Render(IRenderer& renderer) const override;
  [[nodiscard]] float GetX() const override;
  [[nodiscard]] float GetY() const override;
  [[nodiscard]] float GetWidth() const override;
  [[nodiscard]] float GetHeight() const override;
  [[nodiscard]] bool GetActive() const override;

 private:
  Core::Math::ITransform2D& transform;
  Core::Color color;
  bool& active;
};
}  // namespace Renderer2D::Component

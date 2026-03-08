#pragma once

#include "core/components/i-render-component-2d.hpp"
#include "core/color.hpp"

namespace Core {
class IRenderer;

namespace Math {
class ITransform2D;
}

}  // namespace Core

namespace Renderer2D::Components {

class RenderComponent2D final : public Core::Components::IRenderComponent2D {
 public:
  RenderComponent2D(Core::Math::ITransform2D& transform, Core::Color color, bool& active);
  ~RenderComponent2D() override = default;
  void Render(Core::IRenderer& renderer) const override;
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
}  // namespace Renderer2D::Components

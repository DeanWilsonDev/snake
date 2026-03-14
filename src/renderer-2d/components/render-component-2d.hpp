#pragma once

#include "core/rendering/components/i-render-component-2d.hpp"
#include "core/color/color-rgba.hpp"

namespace Core {
namespace Rendering {
class IRenderer;
}
namespace Math {
class ITransform2D;
}

}  // namespace Core

namespace Renderer2D::Components {

class RenderComponent2D final : public Core::Rendering::Components::IRenderComponent2D {
 public:
  RenderComponent2D(
      Core::Math::ITransform2D& transform, Core::Color::ColorRGBA color, bool& active
  );
  ~RenderComponent2D() override = default;
  void Render(const Core::Rendering::IRenderer& renderer) const override;
  [[nodiscard]] float GetX() const override;
  [[nodiscard]] float GetY() const override;
  [[nodiscard]] float GetWidth() const override;
  [[nodiscard]] float GetHeight() const override;
  [[nodiscard]] bool GetActive() const override;

 private:
  Core::Math::ITransform2D& transform;
  Core::Color::ColorRGBA color;
  bool& active;
};
}  // namespace Renderer2D::Components

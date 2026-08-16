#pragma once

#include "core/rendering/components/i-render-component-2d.hpp"
#include "core/color/color-rgba.hpp"

namespace Core {
namespace Rendering {
class IRenderer;
}
namespace Spatial {
class ITransform2D;
}

}  // namespace Core

namespace Renderer2D::Components {

class RenderComponent2D final : public Core::Rendering::Components::IRenderComponent2D {
 public:
  RenderComponent2D(
      Core::Spatial::ITransform2D& transform, Core::Color::ColorRGBA color, const bool& active
  );
  ~RenderComponent2D() override = default;
  void BeginPlay() override;
  void Update(const float) override;
  void Render(const Core::Rendering::IRenderer& renderer) const override;

  void DebugUpdate() const override;
  void DebugRender() const override;
   
  [[nodiscard]] float GetX() const override;
  [[nodiscard]] float GetY() const override;
  [[nodiscard]] float GetWidth() const override;
  [[nodiscard]] float GetHeight() const override;
  [[nodiscard]] const bool& GetActive() const override;

 private:
  Core::Spatial::ITransform2D& transform;
  Core::Color::ColorRGBA color;
  const bool& active;
};
}  // namespace Renderer2D::Components

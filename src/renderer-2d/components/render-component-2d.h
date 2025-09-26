#pragma once

#include "renderer-2d/components/i-render-component-2d.h"
#include "core/color.h"
#include "core/math/size-2d.hpp"
#include "core/math/vector-2d.hpp"

namespace Core::Math {
class ITransform2D;
}
namespace Renderer2D {
class IRenderer;
}

namespace Renderer2D::Component {

class RenderComponent2D final : public IRenderComponent2D {
 public:
  RenderComponent2D(
      Core::Math::ITransform2D& transform, Core::Color color,
      bool enabled
  );
  ~RenderComponent2D() override = default;
  void Render(IRenderer& renderer) const override;
  void SetEnabled(bool enabled) override;
  [[nodiscard]] float GetX() const override;
  [[nodiscard]] float GetY() const override;
  [[nodiscard]] float GetWidth() const override;
  [[nodiscard]] float GetHeight() const override;
  [[nodiscard]] bool GetEnabled() const override;

 private:
  Core::Math::ITransform2D& transform;
  Core::Color color;
  bool enabled;
};
}  // namespace Renderer2D::Component
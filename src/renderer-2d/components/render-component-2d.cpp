//
// Created by Dean Wilson on 28/5/2025.
//

#include "renderer-2d/components/render-component-2d.h"

#include <umbra/log.h>
#include "core/math/i-transform-2d.hpp"
#include "renderer-2d/i-renderer.h"

namespace Renderer2D::Component {

RenderComponent2D::RenderComponent2D(
    Core::Math::ITransform2D& transform, const Core::Color color, bool& active
)
    : transform(transform), color(color), active(active)
{
}

void RenderComponent2D::Render(IRenderer& renderer) const
{
  if (!active) {
    LOG_CORE_TRACE(
        "[RenderComponent2D] Component [{}] Disabled - Skipping Render",
        static_cast<void*>(const_cast<RenderComponent2D*>(this))
    );
    return;
  }

  auto position = transform.GetPosition();
  const auto scale = transform.GetScale();

  LOG_CORE_DEBUG(
      "[RenderComponent2D] Drawing with renderer [{}]: at position ({}, {}), with width ({}, {})",
      static_cast<void*>(&renderer),
      position.x,
      position.y,
      scale.GetWidth(),
      scale.GetHeight()
  );

  // Side Quest: [RenderComponent2D] Allow for rendering different shapes and Sprites
  renderer.DrawRectangle(position.x, position.y, scale.GetWidth(), scale.GetHeight(), color);
}

float RenderComponent2D::GetX() const
{
  return this->transform.GetPosition().x;
}
float RenderComponent2D::GetY() const
{
  return this->transform.GetPosition().y;
}
float RenderComponent2D::GetWidth() const
{
  return this->transform.GetScale().GetWidth();
}
float RenderComponent2D::GetHeight() const
{
  return this->transform.GetScale().GetHeight();
}
bool RenderComponent2D::GetActive() const
{
  return this->active;
}
}  // namespace Renderer2D::Component

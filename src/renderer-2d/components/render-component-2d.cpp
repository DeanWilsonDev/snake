//
// Created by Dean Wilson on 28/5/2025.
//

#include "renderer-2d/components/render-component-2d.h"

#include "core.h"
#include "log.h"
#include "renderer-2d/i-renderer.h"

namespace Renderer2D::Component {

RenderComponent2D::RenderComponent2D(
    Core::Math::Vector2D& position, Core::Math::Size2D& size, const Core::Color color,
    const bool enabled = true
)
    : position(position), size(size), color(color), enabled(enabled)
{
}

void RenderComponent2D::Render(IRenderer& renderer) const
{
  if (!enabled) {
    LOG_CORE_TRACE(
        "[RenderComponent2D] Component [{}] Disabled - Skipping Render",
        static_cast<void*>(const_cast<RenderComponent2D*>(this))
    );
    return;
  }

  LOG_CORE_DEBUG("[RenderComponent2D] Drawing with renderer [{}]", static_cast<void*>(&renderer));

  // Side Quest: [RenderComponent2D] Allow for rendering different shapes and Sprites
  renderer.DrawRectangle(position.x, position.y, size.GetWidth(), size.GetHeight(), color);
}

float RenderComponent2D::GetX() const
{
  return this->position.x;
}
float RenderComponent2D::GetY() const
{
  return this->position.y;
}
float RenderComponent2D::GetWidth() const
{
  return this->size.GetWidth();
}
float RenderComponent2D::GetHeight() const
{
  return this->size.GetHeight();
}
bool RenderComponent2D::GetEnabled() const
{
  return this->enabled;
}
void RenderComponent2D::SetEnabled(const bool enabled)
{
  this->enabled = enabled;
}
}  // namespace Renderer2D::Component

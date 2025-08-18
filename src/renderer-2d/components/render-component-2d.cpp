//
// Created by Dean Wilson on 28/5/2025.
//

#include "renderer-2d/components/render-component-2d.h"

#include "core.h"
#include "log.h"
#include "renderer-2d/i-renderer.h"

namespace Renderer2D::Component {

RenderComponent2D::RenderComponent2D(
    const float width, const float height, const float positionX, const float positionY,
    const Core::Color color
)
    : position({positionX, positionY}), size({width, height}), color(color)
{
}
RenderComponent2D::RenderComponent2D(
    Core::Math::Vector2D position, Core::Math::Size2D size, Core::Color color
)
    : position(position), size(size), color(color)
{
}

void RenderComponent2D::Render(IRenderer& renderer) const
{
  LOG_CORE_DEBUG("[RenderComponent2D] Drawing with renderer [{}]", static_cast<void*>(&renderer));

  // Side Quest: [RenderComponent2D] Allow for rendering different shapes and Sprites
  renderer.DrawRectangle(position.x, position.y, size.GetWidth(), size.GetHeight(), color);
}

void RenderComponent2D::SetPosition(const float x, const float y)
{
  this->position.x = x;
  this->position.y = y;
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
}  // namespace Renderer2D::Component

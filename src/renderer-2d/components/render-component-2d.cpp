//
// Created by Dean Wilson on 28/5/2025.
//

#include "renderer-2d/components/render-component-2d.hpp"
#include "core/color.hpp"
#include "core/math/i-transform-2d.hpp"
#include "core/i-renderer.hpp"

namespace Renderer2D::Components {

RenderComponent2D::RenderComponent2D(
    Core::Math::ITransform2D& transform, const Core::Color color, bool& active
)
    : transform(transform), color(color), active(active)
{
}

void RenderComponent2D::Render(Core::IRenderer& renderer) const
{
  if (!active) {
    return;
  }

  auto position = transform.GetPosition();
  const auto scale = transform.GetScale();

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
}  // namespace Renderer2D::Components

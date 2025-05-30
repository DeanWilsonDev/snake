//
// Created by Dean Wilson on 28/5/2025.
//

#include "render-component-2d.h"
#include "../../core/types.h"

namespace Renderer2D::Component {

RenderComponent2D::RenderComponent2D(
    float width, float height, float positionX, float positionY, Core::Color color
)
    : width(width), height(height), positionX(positionX), positionY(positionY), color(color)
{
}

void RenderComponent2D::Render(IRenderer& renderer) const
{
  // TODO: this function should really render different shapes. Maybe even just a sprite would be
  renderer.DrawRectangle(positionX, positionY, width, height, color);
}

void RenderComponent2D::SetPosition(const float x, const float y)
{
  this->positionX = x;
  this->positionY = y;
}
float RenderComponent2D::GetX() const
{
  return this->positionY;
}
float RenderComponent2D::GetY() const
{
  return this->positionY;
}
float RenderComponent2D::GetWidth() const
{
  return this->width;
}
float RenderComponent2D::GetHeight() const
{
  return this->height;
}

}  // namespace Render::Component

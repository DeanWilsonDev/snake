//
// Created by Dean Wilson on 28/5/2025.
//

#include "renderer-2d/components/render-component-2d.h"
#include "renderer-2d/irenderer.h"

namespace Renderer2D::Component {

RenderComponent2D::RenderComponent2D(
    const float width, const float height, const float positionX, const float positionY,
    const UserInterface::Color color
)
    : width(width), height(height), positionX(positionX), positionY(positionY), color(color)
{
}

void RenderComponent2D::Render(IRenderer& renderer) const
{
  // Side Quest [RenderComponent2D] Allow for rendering different shapes and Sprites
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

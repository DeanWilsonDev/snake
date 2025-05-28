//
// Created by Dean Wilson on 28/5/2025.
//

#include "render-component-2d.h"
#include "../core/irenderer.h"

namespace Component {

RenderComponent2D::RenderComponent2D(float size, float positionX, float positionY, Core::Color color)
    : size(size), positionX(positionX), positionY(positionY), color(color)
{
}
void RenderComponent2D::Render(IRenderer& renderer) const
{
  // TODO: this function should really render different shapes. Maybe even just a sprite would be good
  renderer.DrawRectangle(positionX, positionY, size, size, color);
}

void RenderComponent2D::SetPosition(float x, float y)
{
  this->positionX = x;
  this->positionY = y;
}

}  // namespace Component

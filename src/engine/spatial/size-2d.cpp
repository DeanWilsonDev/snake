#include "size-2d.hpp"

namespace Engine::Spatial {

Size2D::Size2D(const float width, const float height) : width(width), height(height) {}

Size2D::Size2D(const float size) : width(size), height(size) {}

Size2D::Size2D(const Core::Spatial::ISize2D& other)
    : width(other.GetWidth()), height(other.GetHeight()) {};

float Size2D::GetWidth() const
{
  return this->width;
}
float Size2D::GetHeight() const
{
  return this->height;
}

void Size2D::SetWidth(const float width)
{
  this->width = width;
}

void Size2D::SetHeight(const float height)
{
  this->height = height;
}

void Size2D::Set(const float width, const float height)
{
  this->width = width;
  this->height = height;
}

Size2D& Size2D::operator=(const Core::Spatial::ISize2D& other)
{
  this->width = other.GetWidth();
  this->height = other.GetHeight();
  return *this;
}

}  // namespace Engine::Spatial

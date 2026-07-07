//
// Created by Dean Wilson on 26/7/2025.
//

#pragma once
#include <string>
#include "core/spatial/i-size-2d.hpp"

namespace Engine::Spatial {

struct Size2D : public Core::Spatial::ISize2D {
 public:
  float width = 0.0f;
  float height = 0.0f;

  Size2D() = default;
  Size2D(const float width, const float height);
  Size2D(const float size);
  Size2D(const Core::Spatial::ISize2D& other);

  [[nodiscard]] float GetWidth() const;
  [[nodiscard]] float GetHeight() const;

  void SetWidth(const float width);
  void SetHeight(const float height);
  void Set(const float width, const float height);

  inline static Size2D Zero() { return {0, 0}; }

  inline std::string ToString() const
  {
    return "{width: " + std::to_string(width) + ", height: " + std::to_string(height) + "}";
  }

  Size2D& operator=(const Core::Spatial::ISize2D& other);
};

}  // namespace Engine::Spatial

//
// Created by Dean Wilson on 26/7/2025.
//

#pragma once
#include <string>

namespace Engine::Spatial {

struct Size2D {
 public:
  float width = 0.0f;
  float height = 0.0f;

  Size2D() = default;
  Size2D(const float w, const float h) : width(w), height(h) {}
  Size2D(const float size) : width(size), height(size) {}

  [[nodiscard]] float GetWidth() const { return this->width; }
  [[nodiscard]] float GetHeight() const { return this->height; }

  void SetWidth(const float w) { this->width = w; }
  void SetHeight(const float h) { this->height = h; }
  void Set(const float w, const float h)
  {
    this->width = w;
    this->height = h;
  }
  inline static Size2D Zero() { return {0, 0}; }
  inline std::string ToString() const
  {
    return "{width: " + std::to_string(width) + ", height: " + std::to_string(height) + "}";
  }
};

}  // namespace Core::Math

///
/// Created by Dean Wilson 7th July 2026
///

#pragma once
#include <string>

namespace Core::Spatial {

struct ISize2D {
 public:
  ~ISize2D() = default;
  virtual float GetWidth() const = 0;
  virtual float GetHeight() const = 0;

  virtual void SetWidth(const float w) = 0;
  virtual void SetHeight(const float h) = 0;
  virtual void Set(const float w, const float h) = 0;
  virtual inline std::string ToString() const = 0;
};

}  // namespace Engine::Spatial

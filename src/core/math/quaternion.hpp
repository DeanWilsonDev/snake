//
// Created by Dean Wilson on 25/6/2025.
//

#pragma once

#include <cmath>

namespace Core::Math {
struct Quaternion {
 public:
  Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  inline static Quaternion Identity() { return Quaternion(0, 0, 0, 1); }

  inline void Normalize()
  {
    float mag = std::sqrt(x * x + y * y + z * z + w * w);
    if (mag > 0.0f) {
      x /= mag;
      y /= mag;
      z /= mag;
      w /= mag;
    }
  }

  inline Quaternion operator*(const Quaternion& q) const
  {
    return Quaternion(
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w - z * q.x,
        w * q.z + x * q.y - y * q.x - z * q.w,
        w * q.w - x * q.x - y * q.y - z * q.z
    );
  }

  [[nodiscard]] inline Quaternion Inverse() const
  {
    // assuming a unit quaternion
    return Quaternion(-x, -y, -z, -w);
  }
};

}  // namespace Core::Math

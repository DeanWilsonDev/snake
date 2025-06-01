//
// Created by Dean Wilson on 1/6/2025.
//

#pragma once
#include <cmath>
using namespace std;

namespace Core::Math {

struct Vector2D {
 public:
  Vector2D() = default;

  Vector2D(const float x, const float y)
  {
    this->x = x;
    this->y = y;
  }

  inline float& operator[](int i) { return ((&x)[i]); }

  inline Vector2D& operator*=(const float s)
  {
    this->x *= s;
    this->y *= s;
    return (*this);
  }

  inline Vector2D& operator/=(float s)
  {
    s = 1.0f / s;
    this->x *= s;
    this->y *= s;
    return (*this);
  }

  inline Vector2D& operator+=(const Vector2D& v)
  {
    this->x += v.x;
    this->y += v.y;
    return (*this);
  }

  inline Vector2D& operator-=(const Vector2D& v)
  {
    this->x -= v.x;
    this->y -= v.y;
    return (*this);
  }

  inline Vector2D operator*(const Vector2D& v, float s) const { return {v.x * s, v.y * s}; }

  inline Vector2D operator/(const Vector2D& v, float s) const
  {
    s = 1.0f / s;
    return {v.x * s, v.y * s};
  }

  inline Vector2D operator-(const Vector2D& v) const { return {-v.x, -v.y}; }

  inline Vector2D operator+(const Vector2D& a, const Vector2D& b) const
  {
    return {a.x + b.x, a.y + b.y};
  }

  inline Vector2D operator-(const Vector2D& a, const Vector2D& b) const
  {
    return {a.x - b.x, a.y - b.y};
  }

  inline static float Magnitude(const Vector2D& v) { return (sqrt((v.x * v.x) + (v.y * v.y))); }

  /*
   * To normalize a 2D vector, you divide each component of the vector by its magnitude (length).
   * This scales the vector to have a length of `1` (making it a unit vector) while preserving its
   * direction.
   */
  inline static Vector2D Normalize(const Vector2D& v)
  {
    const float length = Magnitude(v);
    if (length == 0) {
      return Zero();
    }
    return {v.x / length, v.y / length};
  }

  inline static float Dot(const Vector2D& a, const Vector2D& b) { return (a.x * b.x + a.y * b.y); }

  /*
   * In 2D vectors, the cross-product doesn't produce another vector (like in 3D).
   * Instead, a scalar value is returned that represents the signed area of the parallelogram formed
   * by the two vectors. This scalar value is often used in 2D for:
   *   1. Determining the relative orientation (clockwise or counterclockwise) of vectors.
   *   2. Computing the area of shapes or detecting when vectors point in the same direction.
   */
  inline static float Cross(const Vector2D& a, const Vector2D& b)
  {
    return (a.x * b.y) - (a.y * b.x);
  }

  inline static Vector2D Zero() { return {0, 0}; }

  // Properties:
 public:
  float x, y;
};
}  // namespace Core::Math

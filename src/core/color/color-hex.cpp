#include "color-rgba.hpp"
#include "color-hex.hpp"

#include <cstdint>

namespace Core {
namespace Color {

inline ColorRGBA ColorHex::ToRGBA()
{
  return ColorRGBA::From(*this);
};

inline ColorHex ColorHex::From(const ColorRGBA& color)
{
  return {
      static_cast<uint32_t>(color.red) << 24 | static_cast<uint32_t>(color.green) << 16 |
      static_cast<uint32_t>(color.blue) << 8 | static_cast<uint32_t>(color.alpha)
  };
};

}  // namespace Color
}  // namespace Core

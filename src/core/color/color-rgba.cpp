
#include "color-rgba.hpp"
#include "color-hex.hpp"

namespace Core {
namespace Color {

ColorHex ColorRGBA::ToHex()
{
  return ColorHex::From(*this);
}

inline ColorRGBA ColorRGBA::From(const ColorHex& hex)
{
  return {
      static_cast<unsigned char>((hex.value >> 24) & 0xFF),
      static_cast<unsigned char>((hex.value >> 16) & 0xFF),
      static_cast<unsigned char>((hex.value >> 8) & 0xFF),
      static_cast<unsigned char>((hex.value) & 0xFF),
  };
};
}  // namespace Color
}  // namespace Core

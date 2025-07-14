#pragma once

namespace Core {

typedef struct {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
} Color;

inline extern const Color COLOR_BLACK = {0, 0, 0, 255};
inline extern const Color COLOR_WHITE = {255, 255, 255, 255};
inline extern const Color COLOR_RED = {255, 0, 0, 255};
inline extern const Color COLOR_GREEN = {0, 255, 0, 255};
inline extern const Color COLOR_BLUE = {0, 0, 255, 255};

}  // namespace Core

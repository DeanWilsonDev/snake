//
// Created by Dean Wilson on 6/7/2025.
//

#pragma once

namespace Core {

/**
 * Generates a random integer value within the specified range [min, max].
 * If the value of min is greater than max, their values are swapped.
 *
 * @param min The lower bound of the range.
 * @param max The upper bound of the range.
 * @return A random integer value within the range [min, max].
 */
inline int GetRandomValue(int min, int max)
{
  int value = 0;

  if (min > max) {
    const int tmp = max;
    max = min;
    min = tmp;
  }

  value = (rand() % (abs(max - min) + 1) + min);

  return value;
}
}  // namespace Core

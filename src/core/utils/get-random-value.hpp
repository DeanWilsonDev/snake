#pragma once

#include <random>

namespace Core::Utils{

/**
 * Generates a random integer value within the specified range [min, max].
 *
 * @param min The lower bound of the range.
 * @param max The upper bound of the range.
 * @return A random integer value within the range [min, max].
 */
inline int GetRandomValue(int min, int max)
{
  static std::mt19937 randomEngine{std::random_device{}()};
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(randomEngine);
}
}  // namespace Core

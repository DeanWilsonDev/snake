///
/// Created by Dean Wilson 5th July 2026
///

#pragma once

#include <unordered_set>

namespace Engine::Entities {

struct EntityLifecycleState {
  std::unordered_set<int>& beginPlayFiredIds;
  std::unordered_set<int>& activeLastFrame;
};

}  // namespace Engine::Entities

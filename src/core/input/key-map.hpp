//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once
#include <unordered_map>
#include <vector>
#include "core/input/key-binding.hpp"

namespace Core::Input {

using KeyMap = std::unordered_map<int, std::vector<KeyBinding>>;
}  // namespace Core::Input

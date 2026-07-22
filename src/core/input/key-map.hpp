//
// Created by Dean Wilson on 22nd July 2026
//

#pragma once
#include <vector>
#include <array>
#include "core/input/key-code.hpp"
#include "core/input/action.hpp"

namespace Core::Input {
using KeyMap = std::array<std::vector<KeyCode>, static_cast<size_t>(Action::Count)>;
}

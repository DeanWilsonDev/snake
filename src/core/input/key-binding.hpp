//
// Created by Dean Wilson on 23rd July 2026
//

#pragma once

#include "core/input/key-code.hpp"
#include "core/input/action-value.hpp"

namespace Core::Input {

struct KeyBinding {
  KeyCode key;
  ActionValue contribution;
};

}  // namespace Core::Input

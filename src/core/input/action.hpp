//
// Created by Dean Wilson 23rd July 2026
//

#pragma once

#include <string>
#include "core/input/action-value-type.hpp"

namespace Core::Input {
struct Action {
 public:
  int id;
  std::string name;
  ActionValueType type = ActionValueType::Boolean;
  bool isComposite = false;
};
}  // namespace Core::Input

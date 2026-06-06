//
// Created by Dean Wilson 6th June 2026
//

#pragma once

namespace Core {

class IInitialize {
 public:
  virtual ~IInitialize() = default;
  virtual void Initialize() = 0;
};

}  // namespace Core

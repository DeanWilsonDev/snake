//
// Created by Dean Wilson 6th June 2026
//

#pragma once

namespace Core {

class IBeginPlay {
 public:
  virtual ~IBeginPlay() = default;
  virtual void BeginPlay() = 0;
};

}  // namespace Core

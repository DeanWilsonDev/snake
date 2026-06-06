//
// Created by Dean Wilson 6th June 2026
//

#pragma once

namespace Core {

class IOnBeginPlay {
 public:
  virtual ~IOnBeginPlay() = default;
  virtual void OnBeginPlay() = 0;
};

}  // namespace Core

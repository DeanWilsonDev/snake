//
// Created by Dean Wilson 6th June 2026
//

#pragma once

namespace Core {

class IOnRegistration {
 public:
  virtual ~IOnRegistration() = default;
  virtual void OnRegistration() = 0;
};

}  // namespace Core

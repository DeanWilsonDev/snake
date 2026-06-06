//
// Created by Dean Wilson 6th June 2026
//

#pragma once

namespace Core {

class IOnActivate {
 public:
  virtual ~IOnActivate() = default;
  virtual void OnActivate() = 0;
};

}  // namespace Core

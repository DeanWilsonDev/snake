//
// Created by Dean Wilson on 22nd July 2026.
//

#pragma once

namespace Core::Systems {
class IDispatcher {
 public:
  virtual ~IDispatcher() = default;
  virtual void Run() = 0;
};
}  // namespace Core::Systems

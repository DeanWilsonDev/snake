//
// Created by Dean Wilson 28th February 2026
//

#pragma once

/*
 * Why is a debug interface in Core instead of the Debug module?
 *
 * This interface has been placed in Core to reduce coupling between the Debug Module and the Core
 * Module. Since objects in Core will need to implement this interface, it makes sense to declare it
 * here rather than coupling all implementing classes to the debug module.
 *
 * Additionally, This interface simply enables objects to perform debug actions, not what those
 * actions involve. That is why it lives in the Core Module
 */

namespace Core {
namespace Debug {

class IDebugable {
 public:
  virtual ~IDebugable() = default;
  virtual void DebugUpdate() const = 0;
  virtual void DebugRender() const = 0;
};

}  // namespace Debug
}  // namespace Core

///
/// Created by Dean Wilson 29th May 2026
///

#pragma once

namespace Core {
namespace Scenes {

// 1UP: If this list grows and more data is needed here, promote these to classes and use polymorphism
enum class SceneLifetime {
  Persistent,  // Reuse same instance across visits
  Transient    // Recreate fresh on every visit
};

}
}  // namespace Core

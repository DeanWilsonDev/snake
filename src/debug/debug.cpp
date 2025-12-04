#include "debug.hpp"
#include <utility>
#include <memory>
#include "i-debug-hud.hpp"

namespace Debug {

static std::shared_ptr<IDebugHUD> ActiveDebugHUD;

IDebugHUD& GetActiveDebugHUD()
{
  return *ActiveDebugHUD;
}

void SetActiveDebugHUD(std::shared_ptr<IDebugHUD> hud){
  ActiveDebugHUD = std::move(hud);
}
}  // namespace Debug

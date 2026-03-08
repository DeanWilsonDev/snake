//
// Created by Dean Wilson on 6/7/2025.
//

#include "user-interface-manager.hpp"
#include "i-game-ui.hpp"
#include "core/render-component-2d-manager.hpp"

namespace Core {
UserInterfaceManager::UserInterfaceManager(const Core::RenderComponent2DManager& renderManager)
    : renderManager(renderManager)
{
}

}  // namespace Core

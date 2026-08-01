//
// Created by Dean Wilson on 1st August 2026
//

#pragma once

namespace Core::Entities {
class IEntityManager;
}

namespace Core::Events {
class IEventBus;
}

namespace Core::Systems {
class IGameSystemManager;
}

namespace Core::Scenes {

struct SceneBaseParams {
  Core::Entities::IEntityManager& entityManager;
  Core::Systems::IGameSystemManager& gameSystemManager;
  Core::Events::IEventBus& eventBus;
};


}  // namespace Core::Scenes

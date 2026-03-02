.
├── src
│   ├── core
│   │   ├── color.hpp
│   │   ├── components
│   │   │   ├── i-component.hpp
│   │   │   ├── transform-component-2d.cpp
│   │   │   └── transform-component-2d.hpp
│   │   ├── core.hpp
│   │   ├── entity
│   │   │   ├── entity.cpp
│   │   │   ├── entity.hpp
│   │   │   ├── game-entity.cpp
│   │   │   ├── game-entity.hpp
│   │   │   ├── game-entity-manager.cpp
│   │   │   ├── game-entity-manager.hpp
│   │   │   └── i-game-entity.hpp
│   │   ├── geometry
│   │   │   └── rectangle.hpp
│   │   ├── i-debugable.hpp
│   │   ├── i-game.hpp
│   │   ├── i-game-state.hpp
│   │   ├── implementation-manager.hpp
│   │   ├── i-state-machine.hpp
│   │   ├── i-updatable.hpp
│   │   ├── math
│   │   │   ├── i-transform-2d.hpp
│   │   │   ├── quaternion.hpp
│   │   │   ├── size-2d.hpp
│   │   │   ├── transform-2d.hpp
│   │   │   └── vector-2d.hpp
│   │   ├── state-machine.cpp
│   │   └── state-machine.hpp
│   ├── debug
│   │   ├── debug.hpp
│   │   ├── debug-hud.cpp
│   │   ├── debug-hud.hpp
│   │   ├── debug-node.hpp
│   │   ├── debug-value.hpp
│   │   └── i-debug-hud.hpp
│   ├── engine
│   │   ├── application.cpp
│   │   ├── application.hpp
│   │   ├── config
│   │   │   ├── engine-config.h
│   │   │   └── project-settings.hpp
│   │   ├── dependency-injection
│   │   │   ├── dependency-injector.cpp
│   │   │   └── dependency-injector.hpp
│   │   └── input
│   │       ├── input-action.hpp
│   │       ├── input-system.cpp
│   │       └── input-system.hpp
│   ├── game
│   │   ├── game.cpp
│   │   ├── game.hpp
│   │   ├── game-objects
│   │   │   ├── apple.cpp
│   │   │   ├── apple.hpp
│   │   │   ├── snake.cpp
│   │   │   ├── snake.hpp
│   │   │   ├── snake-segment.cpp
│   │   │   └── snake-segment.hpp
│   │   ├── game-state
│   │   │   ├── game-over-state.cpp
│   │   │   ├── game-over-state.hpp
│   │   │   ├── gameplay-state.cpp
│   │   │   ├── gameplay-state.hpp
│   │   │   ├── gameplay-state-machine.cpp
│   │   │   ├── gameplay-state-machine.hpp
│   │   │   ├── main-menu-state.cpp
│   │   │   └── main-menu-state.hpp
│   │   ├── settings
│   │   │   └── game-settings.hpp
│   │   └── ui
│   │       ├── game-over-ui.cpp
│   │       ├── game-over-ui.hpp
│   │       ├── gameplay-ui.cpp
│   │       ├── gameplay-ui.hpp
│   │       ├── main-menu-ui.cpp
│   │       └── main-menu-ui.hpp
│   ├── main.cpp
│   ├── physics
│   │   └── collision
│   │       ├── components
│   │       │   ├── collider-component-2d.cpp
│   │       │   └── collider-component-2d.hpp
│   │       └── rectangle-collider-2d.hpp
│   ├── platform
│   │   ├── input
│   │   │   ├── i-input-backend.hpp
│   │   │   └── key-codes.hpp
│   │   └── window
│   │       ├── config
│   │       │   └── window-config.hpp
│   │       ├── i-window.h
│   │       ├── screen.hpp
│   │       ├── window-manager.cpp
│   │       └── window-manager.hpp
│   ├── raylib-facade
│   │   ├── core
│   │   │   ├── raylib-core-facade.cpp
│   │   │   └── raylib-core-facade.hpp
│   │   ├── input
│   │   │   ├── raylib-input-backend-facade.cpp
│   │   │   └── raylib-input-backend-facade.hpp
│   │   ├── renderer
│   │   │   ├── raylib-renderer-facade.cpp
│   │   │   └── raylib-renderer-facade.hpp
│   │   ├── user-interface
│   │   │   ├── raylib-user-interface-facade.cpp
│   │   │   └── raylib-user-interface-facade.hpp
│   │   └── window
│   │       ├── raylib-window-facade.cpp
│   │       └── raylib-window-facade.hpp
│   ├── renderer-2d
│   │   ├── components
│   │   │   ├── i-render-component-2d.hpp
│   │   │   ├── render-component-2d.cpp
│   │   │   └── render-component-2d.hpp
│   │   ├── i-renderable.hpp
│   │   ├── i-renderer.hpp
│   │   ├── render-component-2d-manager.cpp
│   │   └── render-component-2d-manager.hpp
│   └── user-interface
│       ├── i-game-ui.hpp
│       ├── i-user-interface.hpp
│       ├── user-interface-manager.cpp
│       └── user-interface-manager.hpp

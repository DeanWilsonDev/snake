cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

project(Snake LANGUAGES CXX)

include(FetchContent)

# Download Raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG 5.5)
FetchContent_MakeAvailable(raylib)

# Download UmbraLog
FetchContent_Declare(
        UmbraLogging
        GIT_REPOSITORY "https://github.com/UmbraEngine/logging.git"
        GIT_TAG main)

FetchContent_MakeAvailable(UmbraLogging)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})

add_executable(
        ${PROJECT_NAME}
        src/main.cpp
        src/game/game-objects/apple.cpp
        src/engine/application.cpp
        src/game/game-state/game-over-state.cpp
        src/raylib-facade/renderer/raylib-renderer-facade.cpp
        src/raylib-facade/window/raylib-window-facade.cpp
        src/raylib-facade/user-interface/raylib-user-interface-facade.cpp
        src/game/game-objects/snake-segment.cpp
        src/game/game-objects/snake.cpp
        src/game/game-state/gameplay-state-machine.hpp
        src/game/game-state/gameplay-state-machine.cpp
        src/game/game-state/gameplay-state.cpp
        src/renderer-2d/components/render-component-2d.h
        src/renderer-2d/components/render-component-2d.cpp
        src/renderer-2d/i-renderable.h
        src/core/entity.cpp
        src/core/entity.h
        src/renderer-2d/render-component-2d-manager.cpp
        src/renderer-2d/render-component-2d-manager.hpp
        src/renderer-2d/components/i-render-component-2d.h
        src/game/ui/main-menu-ui.hpp
        src/game/ui/main-menu-ui.cpp
        src/engine/config/engine-config.h
        src/platform/window/config/window-config.hpp
        src/game/game-state/main-menu-state.cpp
        src/game/game-state/main-menu-state.hpp
        src/platform/input/key-codes.hpp
        src/raylib-facade/input/raylib-input-facade.cpp
        src/raylib-facade/input/raylib-input-facade.hpp
        src/platform/input/i-input.hpp
        src/game/ui/game-over-ui.cpp
        src/game/ui/game-over-ui.hpp
        src/core/math/transform-2d.hpp
        src/core/math/vector-2d.hpp
        src/core/math/quaternion.hpp
        src/platform/window/screen.hpp
        src/raylib-facade/core/raylib-core-facade.cpp
        src/raylib-facade/core/raylib-core-facade.hpp
        src/core/math/geometry/Rectangle.h
        src/physics/components/collider-component-2d.cpp
        src/physics/components/collider-component-2d.hpp
        src/core/core.h
        src/engine/config/project-settings.hpp
        src/core/dependency-injector.cpp
        src/core/dependency-injector.hpp
        src/game/game.cpp
        src/game/game.hpp
        src/core/i-game.hpp
        src/core/math/size-2d.hpp
        src/user-interface/i-game-ui.hpp
        src/game/ui/gameplay-ui.cpp
        src/game/ui/gameplay-ui.hpp
)

# Include and Link Raylib in the game
target_link_libraries(${PROJECT_NAME} raylib)
include_directories(${raylib_SOURCE_DIR}/src)
message(STATUS "The raylib directory is: ${raylib_SOURCE_DIR}/src")

# Include and Link Umbra Libraries
target_link_libraries(${PROJECT_NAME} UmbraLogging)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG
        ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src ${raylib_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(tests)

# Setup system link to compile_commands directory for LSP config
add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ln -sf ${CMAKE_BINARY_DIR}/compile_commands.json
        ~/.config/clangd/compile_commands/compile_commands.json)

cmake_minimum_required(VERSION 3.25)

project(Snake LANGUAGES CXX)


# ----- Global Project Settings -----

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)


include(FetchContent)


# ------ Dependencies ---------

# Raylib

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
  GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)


# UmbraLog
FetchContent_Declare(
  UmbraLog
  GIT_REPOSITORY "https://github.com/UmbraEngine/UmbraLog.git"
  GIT_TAG main)
FetchContent_MakeAvailable(UmbraLog)


# ---- Game target ----
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
  src/core/entity/entity.cpp
  src/core/entity/entity.h
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
  src/user-interface/i-user-interface.hpp
  src/game/ui/gameplay-ui.cpp
  src/game/ui/gameplay-ui.hpp
  src/core/entity/game-entity-manager.cpp
  src/core/entity/game-entity-manager.hpp
  src/core/entity/game-entity.cpp
  src/core/entity/game-entity.hpp
  src/core/entity/i-game-entity.hpp
  src/core/components/i-component.hpp
  src/core/components/transform-component-2d.cpp
  src/core/components/transform-component-2d.hpp
  src/core/math/i-transform-2d.hpp
  src/debug/debug-hud.cpp
  src/debug/debug-hud.hpp
  src/debug/debug-node.hpp
  src/debug/debug-value.hpp
  src/debug/debug.hpp
  src/debug/i-debug-hud.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)


# Include and Link Libraries
target_link_libraries(${PROJECT_NAME} 
  PRIVATE
  raylib
  umbra_log
)

message(STATUS "The raylib directory is: ${raylib_SOURCE_DIR}/src")


# ---- Compiler-specific options (portable) ----
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /EHsc)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()


# ---- Output dirs (portable acreoss single/multi-config) ----
set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)


# ---- Tests ----
option(SNAKE_BUILD_TESTS "Build tests" OFF)
if(SNAKE_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

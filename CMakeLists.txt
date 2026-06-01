cmake_minimum_required(VERSION 3.25)

project(Snake LANGUAGES CXX)

# ----- Global Project Settings -----

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# ------ Dependencies ---------

# Raylib

set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)
set(BUILD_GAMES
    OFF
    CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
  GIT_TAG 5.5)
FetchContent_MakeAvailable(raylib)

# Firefly

FetchContent_Declare(
  firefly
  GIT_REPOSITORY "https://github.com/DeanWilsonDev/firefly.git"
  GIT_TAG main)
FetchContent_MakeAvailable(firefly)

# ---- Game target ----
add_executable(
  ${PROJECT_NAME}
  src/main.cpp
  src/engine/application/application.cpp
  src/engine/input/input-system.cpp
  src/raylib-facade/renderer/raylib-renderer-facade.cpp
  src/raylib-facade/window/raylib-window-facade.cpp
  src/raylib-facade/user-interface/raylib-user-interface-facade.cpp
  src/renderer-2d/components/render-component-2d.cpp
  src/core/color/color-rgba.cpp
  src/core/color/color-hex.cpp
  src/core/components/transform-component-2d.cpp
  src/renderer-2d/render-component-2d-manager.cpp
  src/core/user-interface/user-interface-manager.cpp
  src/core/logging/log.cpp
  src/raylib-facade/input/raylib-input-backend-facade.cpp
  src/raylib-facade/core/raylib-core-facade.cpp
  src/physics/collision/components/collider-component-2d.cpp
  src/engine/dependency-injection/dependency-injector.cpp
  src/engine/entities/entity-manager.cpp
  src/engine/entities/entity.cpp
  src/engine/state/state-machine.cpp
  src/engine/scenes/scene-manager.cpp
  src/engine/events/event-bus.cpp
  src/engine/ui/render-component-ui-manager.cpp
  src/debug/debug-hud.cpp
  src/snake-game/snake-application.cpp
  src/snake-game/game-state/game-over-state.cpp
  src/snake-game/game-entities/apple.cpp
  src/snake-game/game-entities/snake-segment.cpp
  src/snake-game/game-entities/snake.cpp
  src/snake-game/game-state/gameplay-state-machine.cpp
  src/snake-game/game-state/gameplay-state.cpp
  src/snake-game/game-state/main-menu-state.cpp
  src/snake-game/game-scenes/gameplay-scene.cpp
  src/snake-game/ui/game-over-ui.cpp
  src/snake-game/ui/main-menu-ui.cpp
  src/snake-game/ui/gameplay-ui.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Include and Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raylib firefly)

message(STATUS "The raylib directory is: ${raylib_SOURCE_DIR}/src")

# ---- Compiler-specific options (portable) ----
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /EHsc)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Output dirs (portable acreoss single/multi-config) ----
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
             ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# ---- Tests ----
option(SNAKE_BUILD_TESTS "Build tests" OFF)
if(SNAKE_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# -------------------------
# Test executable
# -------------------------

if(SNAKE_BUILD_TESTS)

  find_package(Cimmerian 1.0 REQUIRED)

  add_executable(test/test-main.cpp)

  target_link_libraries(test_snake PRIVATE ${PROJECT_NAME} Cimmerian::cimmerian)
  target_compile_features(test_snake PRIVATE cxx_std_20)

  if(MSVC)
    target_compile_options(test_snake PRIVATE /W4 /EHsc)
  else()
    target_compile_options(test_snake PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endif()

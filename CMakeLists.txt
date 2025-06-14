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
        src/game/apple.cpp
        src/engine/application.cpp
        src/game/game-state/game-over-state.cpp
        src/game-session.cpp
        src/raylib/renderer/raylib-renderer-adapter.cpp
        src/raylib/window/raylib-window-adapter.cpp
        src/raylib/user-interface/raylib-user-interface-adapter.cpp
        src/game/snake-body.cpp
        src/game/snake.cpp
        src/game/game-state/gameplay-state-machine.h
        src/game/game-state/gameplay-state-machine.cpp
        src/game/game-state/gameplay-state.cpp
        src/renderer-2d/components/render-component-2d.h
        src/renderer-2d/components/render-component-2d.cpp
        src/renderer-2d/irenderable.h
        src/core/entity.cpp
        src/core/entity.h
        src/renderer-2d/render-manager.cpp
        src/renderer-2d/render-manager.hpp
        src/renderer-2d/components/irender-component-2d.h
        src/game/ui/main-menu-ui.hpp
        src/game/ui/main-menu-ui.cpp
        src/engine/config/engine-config.h
        src/platform/window/config/window-config.hpp
        src/game/game-state/main-menu-state.cpp
        src/game/game-state/main-menu-state.hpp
        src/platform/input/key-codes.hpp
        src/raylib/input/raylib-input-adapter.cpp
        src/raylib/input/raylib-input-adapter.hpp
        src/platform/input/iinput.hpp
        src/platform/input/input-manager.cpp
        src/platform/input/input-manager.hpp
        src/game/ui/game-over-ui.cpp
        src/game/ui/game-over-ui.hpp
        src/platform/window/window-manager.cpp
        src/platform/window/window-manager.hpp
        src/core/math/transform-2d.hpp
        src/core/math/vector-2d.hpp
)

# Include and Link Raylib in the game
target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src)
message(STATUS "The raylib directory is: ${raylib_SOURCE_DIR}/src")

# Include and Link Umbra Libraries
target_link_libraries(${PROJECT_NAME} UmbraLogging)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG
        ${CMAKE_CURRENT_SOURCE_DIR})
enable_testing()
add_subdirectory(tests)

# Setup system link to compile_commands directory for LSP config
add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ln -sf ${CMAKE_BINARY_DIR}/compile_commands.json
        ~/.config/clangd/compile_commands/compile_commands.json)

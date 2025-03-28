cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Snake LANGUAGES CXX)

# Download Raylib
include(FetchContent)
FetchContent_Declare(raylib
                     GIT_REPOSITORY "https://github.com/raysan5/raylib.git")
FetchContent_MakeAvailable(raylib)

include_directories(${raylib_SOURCE_DIR}/src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/apple.cpp
  src/application.cpp
  src/game-state.cpp
  src/raylib-renderer.cpp
  src/raylib-window.cpp
  src/raylib-ui.cpp
  src/snake-body.cpp
  src/snake.cpp
)

# Include and Link Raylib in the game
target_link_libraries(${PROJECT_NAME} raylib)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG
                                                 ${CMAKE_CURRENT_SOURCE_DIR})
enable_testing()
add_subdirectory(tests)

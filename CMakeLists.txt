cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

project(Snake LANGUAGES CXX)

include(FetchContent)

# Download Raylib
FetchContent_Declare(raylib
                     GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
                   GIT_TAG 5.5
                 )
FetchContent_MakeAvailable(raylib)


# Download UmbraLogging
FetchContent_Declare(
  UmbraLogging
  GIT_REPOSITORY "https://github.com/UmbraEngine/logging.git"
  GIT_TAG main
)

FetchContent_MakeAvailable(UmbraLogging)


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
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ln -sf ${CMAKE_BINARY_DIR}/compile_commands.json ~/.config/clangd/compile_commands/compile_commands.json
)

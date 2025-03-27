cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.test.cpp)
message(STATUS "Test sources found: ${TEST_SOURCES}")

add_executable(tests
  test-framework.cpp
  main.cpp
)


target_include_directories(tests PRIVATE ../src)
target_link_libraries(tests PRIVATE raylib)


# Add a `make test` target
add_test(NAME RunTests COMMAND tests)

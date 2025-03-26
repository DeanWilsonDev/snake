add_executable(tests
  test-framework.cpp
  apple-test.cpp
)


target_include_directories(tests PRIVATE ../src)
target_link_libraries(tests PRIVATE raylib)


# Add a `make test` target
add_test(NAME RunTests COMMAND tests)

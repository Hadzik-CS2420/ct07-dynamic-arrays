cmake_minimum_required(VERSION 3.20)
project(ct07-dynamic-arrays LANGUAGES CXX)

# Write build/compile_commands.json so C++ IntelliSense knows the real
# include paths and flags instead of guessing at them.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files (excluding main.cpp for tests)
set(LIB_SOURCES
    src/new_and_delete.cpp
    src/two_dimensional_arrays.cpp
    src/dynamic_arrays.cpp
)

# Main executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    ${LIB_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# ==================== Google Test ====================
# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(run_tests
    tests/new_and_delete_test.cpp
    tests/two_dimensional_arrays_test.cpp
    tests/dynamic_arrays_test.cpp
    ${LIB_SOURCES}
)

target_include_directories(run_tests PRIVATE include)
target_link_libraries(run_tests GTest::gtest_main)

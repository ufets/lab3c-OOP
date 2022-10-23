cmake_minimum_required(VERSION 3.21)
project(Google_tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run ../PCB.cpp ../dialog.cpp test.cpp)
include_directories(../)
target_link_libraries(Google_Tests_run gtest gtest_main)
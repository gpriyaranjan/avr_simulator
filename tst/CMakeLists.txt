cmake_minimum_required(VERSION 3.26)

project(ATMegaSIM_tests)
set(CMAKE_CXX_STANDARD 23)

enable_testing()
find_package(GTest REQUIRED)

include_directories(../src/simulation)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_FILES
        simulation/init_test.cpp
        simulation/flags_test.cpp
)

add_executable(init_test ${TEST_FILES})
target_link_libraries(init_test gtest gtest_main)


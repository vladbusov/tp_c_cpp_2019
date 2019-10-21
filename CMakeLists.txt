cmake_minimum_required(VERSION 3.15)
project(dz2)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(
        ${GTEST_INCLUDE_DIRS}
        ./tests
        ./Counter
        ./trivialCounter
)

add_executable(dz2 tests/test.cpp Counter/counter.c trivialCounter/trivialCounter.c Counter/counter.h trivialCounter/trivialCounter.h)



target_link_libraries(
        dz2 ${GTEST_LIBRARIES} Threads::Threads)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
endif()

add_test(test "./test")
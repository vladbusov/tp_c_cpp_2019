cmake_minimum_required(VERSION 3.10)
project(dz2)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror --pedantic")

include_directories(
        ${GTEST_INCLUDE_DIRS}
        ./tests
        ./Counter
        ./trivialCounter
        ./production
)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


add_library(trivialCounter SHARED trivialCounter/trivialCounter.c)
add_library(counter STATIC Counter/counter.c)
add_executable(dz2tests tests/test.cpp)
add_executable(dz2trivial production/prod_trivial.cpp)
add_executable(dz2parallel production/prod_parallel.cpp)
add_executable(maketxt production/maketxt.cpp)

target_link_libraries(
        dz2tests ${GTEST_LIBRARIES} Threads::Threads trivialCounter counter)

target_link_libraries(
        dz2trivial trivialCounter)

target_link_libraries(
        dz2parallel counter)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
endif()

add_test(test "./test")

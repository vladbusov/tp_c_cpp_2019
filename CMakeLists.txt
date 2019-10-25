#cmake_minimum_required(VERSION 3.15)
project(dz2)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")



include_directories(
        ${GTEST_INCLUDE_DIRS}
        ./tests
        ./Counter
        ./trivialCounter
)

# Динамические библиотеки
add_library(dcounter SHARED Counter/counter.h Counter/counter.c)
add_library(dtrivialCounter SHARED trivialCounter/trivialCounter.h trivialCounter/trivialCounter.c)

# Статические библиотеки
add_library(trivialCounter STATIC trivialCounter/trivialCounter.h trivialCounter/trivialCounter.c)
add_library(counter STATIC Counter/counter.h Counter/counter.c)

add_executable(dz2 tests/test.cpp)

target_link_libraries(
        dz2 ${GTEST_LIBRARIES} Threads::Threads dcounter trivialCounter)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
endif()

add_test(test "./test")
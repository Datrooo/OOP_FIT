cmake_minimum_required(VERSION 3.10)
project(BitArrayProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(include)

file(GLOB SOURCES
    "lab1.cpp"
    "bitArray.cpp"
)

file(GLOB TEST_SOURCES
    "lab1_tests.cpp"
)

add_executable(BitArray ${SOURCES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(BitArrayTests ${TEST_SOURCES} bitArray.cpp)
target_link_libraries(BitArrayTests ${GTEST_LIBRARIES} pthread)

cmake_minimum_required(VERSION 3.21)
project(Genetic)

set(CMAKE_CXX_STANDARD 20)

# Find all code files so CLion recognizes them for include.
include_directories(src)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp src/*.c src/*.h tests/*.cpp tests/*.hpp)

add_subdirectory(src)
add_subdirectory(tests)

add_dependencies(GeneticTests GeneticSrc)
target_link_libraries(GeneticTests gtest gtest_main GeneticSrc)

add_executable(${PROJECT_NAME} main.cpp)
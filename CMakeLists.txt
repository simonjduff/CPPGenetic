cmake_minimum_required(VERSION 3.21)
project(Genetic)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(tests)

add_dependencies(GeneticTests GeneticSrc)
target_link_libraries(GeneticTests gtest gtest_main GeneticSrc)

add_executable(${PROJECT_NAME} main.cpp)
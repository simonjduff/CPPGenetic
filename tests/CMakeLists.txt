cmake_minimum_required(VERSION 3.21)
project(GeneticTests)

set(CMAKE_CXX_STANDARD 20)

# Google Test
# https://www.jetbrains.com/help/clion/unit-testing-tutorial.html#adding-framework
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip # 1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
#End Google Test
enable_testing()

set (SRCS CrossbreederTests.cpp)

add_executable(${PROJECT_NAME} ${SRCS})


add_test(NAME tests COMMAND test)
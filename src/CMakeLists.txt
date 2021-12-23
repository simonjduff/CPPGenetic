project(GeneticSrc)

file(GLOB_RECURSE SRCS *.cpp *.hpp *.c *.h)

add_library(${PROJECT_NAME} STATIC ${SRCS})
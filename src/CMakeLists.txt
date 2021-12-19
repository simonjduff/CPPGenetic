project(GeneticSrc)

set(SRCS Genomes.h
        Genomes.cpp)

add_library(${PROJECT_NAME} STATIC ${SRCS})
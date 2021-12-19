project(GeneticSrc)

set(SRCS Genomes.h
        Genomes.cpp
        Crossbreeder.h
        CrossBreeder.cpp)

add_library(${PROJECT_NAME} STATIC ${SRCS})
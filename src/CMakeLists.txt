project(GeneticSrc)

set(SRCS Genomes.h
        Genomes.cpp
        Crossbreeder.h
        Crossbreeder.cpp)

add_library(${PROJECT_NAME} STATIC ${SRCS})
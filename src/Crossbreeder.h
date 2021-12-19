//
// Created by Simon Duff on 19/12/2021.
//

#ifndef GENETIC_CROSSBREEDER_H
#define GENETIC_CROSSBREEDER_H

#include <array>
#include "Genomes.h"

class Crossbreeder {
public:
    Crossbreeder(int genomeBits);
    // Crossbreed returns new genomes based on the combindation of those passed in
    Genome Crossbreed(Genome left, Genome right, std::array<int, 2> cutIndexes);
private:
    int _bitCount;
};


#endif //GENETIC_CROSSBREEDER_H

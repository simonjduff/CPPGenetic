//
// Created by Simon Duff on 19/12/2021.
//

#ifndef GENETIC_CROSSBREEDER_H
#define GENETIC_CROSSBREEDER_H

#include "Genomes.h"

class Crossbreeder {
public:
    Crossbreeder(int genomeBits);
    // Crossbreed returns new genomes based on the combindation of those passed in
    std::array<Genome, 2> Crossbreed(Genome left[], Genome right[], int cutIndexes[]);
private:
    int _bitCount;
};


#endif //GENETIC_CROSSBREEDER_H

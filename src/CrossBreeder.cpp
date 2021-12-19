//
// Created by Simon Duff on 19/12/2021.
//

#include "Crossbreeder.h"

Genome Crossbreeder::Crossbreed(Genome left, Genome right, std::array<int, 2>cutIndexes) {
    std::sort(cutIndexes.begin(), cutIndexes.end());

    Genome mask = (Genome)pow(2, 64-cutIndexes[1])-1;
    mask = mask << cutIndexes[1];
    mask |= (uint64_t)pow(2, cutIndexes[0])-1;
    uint64_t invertedMask = ~mask;

    return (mask & left) | (invertedMask & right);
}
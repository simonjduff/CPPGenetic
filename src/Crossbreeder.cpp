//
// Created by Simon Duff on 19/12/2021.
//

#include <algorithm>
#include "Crossbreeder.h"
#include "CrossbreedExceptions.h"

Genome Crossbreeder::Crossbreed(Genome left, Genome right, std::array<int, 2>cutIndexes) {
    std::sort(cutIndexes.begin(), cutIndexes.end());

    if (sizeof(cutIndexes) > 1) {
        for (int i = 1; i < cutIndexes.size(); i++) {
            if (cutIndexes[i] == cutIndexes[i - 1]) {
                throw CrossbreedExceptions::DuplicateCutException();
            }
        };
    }

    // If the genome was 1 byte, and you cut at 6 and 2, say
    // Then we want two masks
    // 11100011 and 00011100
    // Then apply the first mask to parent1 and the second to parent2
    // to create a new genome with the traits of both parents

    // Create a mask of 1s the size of int64 - first cut
    Genome mask = (Genome)pow(2, 64-cutIndexes[1])-1;
    // Move the first mask all the way left
    mask = mask << cutIndexes[1];
    // Add a mask of 1s the size of right cut
    mask |= (uint64_t)pow(2, cutIndexes[0])-1;
    // Invert the mask for the other parent to map
    uint64_t invertedMask = ~mask;

    return (mask & left) | (invertedMask & right);
}
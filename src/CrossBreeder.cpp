//
// Created by Simon Duff on 19/12/2021.
//

#include "Crossbreeder.h"
#include <iostream>
Crossbreeder::Crossbreeder(int genomeBits) {
    _bitCount = genomeBits;
}

Genome Crossbreeder::Crossbreed(Genome left, Genome right, int *cutIndexes) {
    int int64sRequired = _bitCount / 64;
    if (_bitCount%64 > 0){
        int64sRequired++;
    }

    return 0;
}
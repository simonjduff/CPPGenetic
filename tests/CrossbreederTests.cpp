//
// Created by Simon Duff on 19/12/2021.
//
#include <gtest/gtest.h>
#include "../src/Crossbreeder.h"
#include <memory>

TEST(CrossbreedTests, 90Bits2Cuts) {
    // 90 bits requires two uint64s, but we shouldn't touch the remaining 38 bits.
    // Max size is 2^(N-1) where N is genome width.
    // 1,237,940,039,285,380,274,899,124,223
    // This will be 26 bits of one uint64, and 64 of the next

    uint64_t left[] = {67108863, UINT64_MAX};
    uint64_t right[] = {0, 0};

    auto crossbreeder = std::make_unique<Crossbreeder>(90);

    int cuts[] = {30, 70};
    auto child = crossbreeder->Crossbreed(left, right, cuts);

    // Take the left and right edges of left genome, and the center from right genome
    // mask these out with 1s
    // Right cut is 2^30-1
    // Left cut is at 30, so that's 26 bits of the first uint64 and 4 of the second
    // So second genome is 2^30-1 + 2^63 + 2^62 + 2^61
    uint64_t firstGenome = pow(2,26) - 1;
    uint64_t secondGenome = pow(2, 30) - 1 + pow(2,63) + pow(2,62) + pow(2,61);
    uint64_t masks[] = {firstGenome, secondGenome};

    EXPECT_EQ(child[0],firstGenome);
    EXPECT_EQ(child[1],secondGenome);
}
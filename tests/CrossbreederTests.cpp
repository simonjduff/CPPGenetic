//
// Created by Simon Duff on 19/12/2021.
//
#include <gtest/gtest.h>
#include "../src/Crossbreeder.h"
#include <memory>
#include <format>
#include <bitset>

TEST(CrossbreedTests, 90Bits2Cuts) {
    uint64_t left = UINT64_MAX;
    uint64_t right = 0;

    auto crossbreeder = std::make_unique<Crossbreeder>(90);

    // The cuts count right to left. so a cut at 2 is at binary 10
    int cuts[] = {30, 50};
    auto child = crossbreeder->Crossbreed(left, right, cuts);


    uint64_t mask = pow(2,14)-1;
    // Shift 50, at that pushes 1s before the cut
    mask = mask << 50;
    mask |= (uint64_t)pow(2, 30)-1;
    uint64_t invertedMask = ~mask;

    uint64_t expected = (mask & left) | (invertedMask & right);

    EXPECT_EQ(child,expected);
}
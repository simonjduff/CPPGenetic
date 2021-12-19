//
// Created by Simon Duff on 19/12/2021.
//
#include <gtest/gtest.h>
#include "../src/Crossbreeder.h"
#include <memory>

TEST(CrossbreedTests, 90Bits2Cuts) {
    uint64_t left = UINT64_MAX;
    uint64_t right = 0;

    auto crossbreeder = std::make_unique<Crossbreeder>(90);

    // The cuts count right to left. so a cut at 2 is at binary 10
    std::array<int,2> cuts = {30, 50};
    auto child = crossbreeder->Crossbreed(left, right, cuts);

    Genome expected = 18445618174876450815;
    EXPECT_EQ(child,expected);
}
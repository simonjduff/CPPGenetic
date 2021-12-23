//
// Created by Simon Duff on 19/12/2021.
//
#include <gtest/gtest.h>
#include <string>
#include "Crossbreeder.h"
#include "CrossbreedExceptions.h"

TEST(CrossbreedTests, 90Bits2Cuts) {
    uint64_t left = UINT64_MAX;
    uint64_t right = 0;

    auto crossbreeder = std::make_unique<Crossbreeder>();

    // The cuts count right to left. so a cut at 2 is at binary 10
    // resulting in a mask of 11 at the end.
    std::array<int,2> cuts = {30, 50};
    auto child = crossbreeder->Crossbreed(left, right, cuts);

    Genome expected = 18445618175950192639;
    EXPECT_EQ(child,expected);
}

TEST(CrossbreedTests, Boundaries) {
    uint64_t left = UINT64_MAX;
    uint64_t right = 0;

    auto crossbreeder = std::make_unique<Crossbreeder>();

    std::array<int,2> cuts = {0, 63};
    auto child = crossbreeder->Crossbreed(left, right, cuts);

    Genome expected = 9223372036854775809;
    EXPECT_EQ(child,expected);
}

TEST(CrossbreedTests, OutofBounds) {
    uint64_t left = UINT64_MAX;
    uint64_t right = 0;

    auto crossbreeder = std::make_unique<Crossbreeder>();

    // The cuts count right to left. so a cut at 2 is at binary 10
    std::array<int,2> cuts = {0, 64};
    bool faulted;
    try{
        auto child = crossbreeder->Crossbreed(left, right, cuts);
    }
    catch (CrossbreedExceptions::CutOutOfBoundsException& e){
        faulted = true;
        EXPECT_EQ("Cut 64 is outside the bounds of the genome", std::string(e.what()));
    }
    EXPECT_EQ(true, faulted);
}

TEST(CrossbreedTests, DuplicateCutsNotPermitted){
    uint64_t left = UINT64_MAX;
    uint64_t right = 0;

    bool faulted = false;

    auto crossbreeder = std::make_unique<Crossbreeder>();

    // The cuts count right to left. so a cut at 2 is at binary 10
    std::array<int,2> cuts = {30, 30};

    try{
        auto child = crossbreeder->Crossbreed(left, right, cuts);
    }
    catch (CrossbreedExceptions::DuplicateCutException& e){
        faulted = true;
        EXPECT_EQ("Cannot cut more than once in the same location", std::string(e.what()));
    }
    EXPECT_EQ(true, faulted);
}
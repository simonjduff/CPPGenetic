//
// Created by Simon Duff on 19/12/2021.
//
#include <gtest/gtest.h>
#include <string>
#include "Crossbreeder.h"
#include "CrossbreedExceptions.h"
using namespace std;

TEST(CrossbreedTests, 90Bits2Cuts) {
    uint64_t left = UINT64_MAX;
    uint64_t right = 0;

    auto crossbreeder = std::make_unique<Crossbreeder>();

    // The cuts count right to left. so a cut at 2 is at binary 10
    std::array<int,2> cuts = {30, 50};
    auto child = crossbreeder->Crossbreed(left, right, cuts);

    Genome expected = 18445618174876450815;
    EXPECT_EQ(child,expected);
}

TEST(CrossbreedTests, DuplicateCutsNotPermitted){
    uint64_t left = UINT64_MAX;
    uint64_t right = 0;

    bool faulted = false;

    auto crossbreeder = make_unique<Crossbreeder>();

    // The cuts count right to left. so a cut at 2 is at binary 10
    array<int,2> cuts = {30, 30};

    try{
        auto child = crossbreeder->Crossbreed(left, right, cuts);
    }
    catch (CrossbreedExceptions::DuplicateCutException& e){
        faulted = true;
        EXPECT_EQ("Cannot cut more than once in the same location", string(e.what()));
    }
    EXPECT_EQ(true, faulted);
}
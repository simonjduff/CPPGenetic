//
// Created by Simon Duff on 19/12/2021.
//
#include <gtest/gtest.h>
#include "../src/Genomes.h"
#include <stdio.h>
#include <memory>
TEST(Counter, Increment) {
    auto genomes = std::make_unique<Genomes>(1, 1);
    EXPECT_EQ(1,1);
}
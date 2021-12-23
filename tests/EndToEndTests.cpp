//
// Created by Simon Duff on 22/12/2021.
//

#include <memory>
#include <gtest/gtest.h>
#include "Crossbreeder.h"
#include "Genomes.h"

TEST(EndToEndTests, SmallGenome) {
    auto crossbreeder = std::make_shared<Crossbreeder>();

    auto fitnessTest = [](Genome genome){
        uint64_t mask = pow(2, 31) -1;
        int32_t calc = (int32_t)(genome & mask);

        double result = calc == 999999 ? INT64_MAX : INT32_MAX/(double)abs((calc - 999999));
        return result;
    };

    auto genomeGenerator = [](uint64_t seed){
        return seed;
    };

    auto genetic = std::make_unique<Genomes>(crossbreeder,
                                             genomeGenerator,
                                             fitnessTest,
                                             10000);

    genetic->Run();

    EXPECT_EQ(1,-1);
}
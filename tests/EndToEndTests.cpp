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
        return genome == 999999 ? 1 : abs(1./(genome - 999999));
    };

    auto genomeGenerator = [](uint64_t seed){
        return seed;
    };

    auto genetic = std::make_unique<Genomes>(crossbreeder,
                                             genomeGenerator,
                                             fitnessTest,
                                             10000);

    genetic->Run();
}
//
// Created by Simon Duff on 18/12/2021.
//

#ifndef GENETIC_GENOMES_H
#define GENETIC_GENOMES_H

#include <memory>
#include <array>
#include <map>
#include <atomic>
#include <time.h>
#include <random>
#include <functional>
#include "Crossbreeder.h"
#include "Types.h"

class Genomes {
public:
    /*
     * populationCount - number of organisms
     */
    Genomes(std::shared_ptr<Crossbreeder> crossbreeder,
            std::function<Genome(uint64_t seed)> genomeGenerator,
            std::function<Fitness(Genome)> fitness,
            int populationCount);
    void Run();

private:
    const int _cullPercentage = 20;
    const int _mutationPercentage = 5;
    int _populationCount;
    std::shared_ptr<Genome[]> _genomes;
    std::unique_ptr<std::map<GenomeIndex,Fitness>> _fitness;
    static std::atomic<int> CurrentFitnessIndex;
    std::uniform_int_distribution<int> _randomGenomeIndex;
    std::uniform_int_distribution<int> _randomCutPoint;
    std::mt19937 _rng;
    std::shared_ptr<Crossbreeder> _crossbreeder;
    std::function<Fitness(Genome)> _fitnessTest;
    std::function<Genome(uint64_t)> _genomeGenerator;

    // create random sample population
    void BuildInitialPopulation();

    // Spin up N threads (maybe 10) until all the fitnesses are calculated
    void CalculateFitness();

    // select _cullPercentage * 2 genomes to crossbreed, overwriting the genomes of _cullPercentage in _genomes
    // select N points (2?) to cut in the genome and crossbreed with another genome
    void CrossBreed();

    // do mutation
    void Mutate();

    void SortFitness();

    static void FitnessThread(int threadNumber,
                              int populationCount,
                              std::function<Fitness(Genome)> fitnessTest,
                              std::shared_ptr<Genome[]> genomes);
};

#endif //GENETIC_GENOMES_H

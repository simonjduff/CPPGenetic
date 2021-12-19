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

typedef int GenomeIndex;
typedef double Fitness;
typedef uint64_t Genome;

class Genomes {
public:
    /*
     * genomeSize - number of int64s required to hold the genome
     * populationCount - number of organisms
     */
    Genomes(int genomeSize, int populationCount);

private:
    int _genomeSize;
    int _populationCount;
    std::unique_ptr<Genome[]> _genomes;
    std::unique_ptr<std::map<GenomeIndex,Fitness>> _fitness;
    std::atomic<int> _currentFitnessIndex = 0;
    const int _cullPercentage = 20;
    std::uniform_int_distribution<int> _randomGenomeIndex;
    std::uniform_int_distribution<int> _randomCutPoint;
    std::mt19937 _rng;

    Genome* getGenome(int index);

    void setGenome(int index, Genome genome[]);

    // create random sample population
    void buildInitialPopulation();

    // select _cullPercentage * 2 genomes to crossbreed, overwriting the genomes of _cullPercentage in _genomes
    // select N points (2?) to cut in the genome and crossbreed with another genome
    void crossBreed();

    // Spin up N threads (maybe 10) until all the fitnesses are calculated
    void calculateFitness();

    // do mutation
    void mutate();

    void fitnessThread();

    void sortFitness();
};

#endif //GENETIC_GENOMES_H

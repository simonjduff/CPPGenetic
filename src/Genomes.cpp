//
// Created by Simon Duff on 18/12/2021.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "Genomes.h"

Genomes::Genomes(std::shared_ptr<Crossbreeder> crossbreeder,
                 std::function<Genome(uint64_t)> genomeGenerator,
                 std::function<Fitness(Genome)> fitnessTest,
                 int populationCount){
    _populationCount = populationCount;
    _genomes = std::make_shared<Genome[]>(populationCount);
    _fitness = std::make_unique<std::map<GenomeIndex,Fitness>>();
    std::mt19937 _rng(time(NULL));
    _randomGenomeIndex = std::uniform_int_distribution<int> (0, _populationCount - 1);
    _randomCutPoint = std::uniform_int_distribution<int> (0, 64);
    _crossbreeder = crossbreeder;
    _fitnessTest = fitnessTest;
    _genomeGenerator = genomeGenerator;

    for (int i=0;i<populationCount;i++){
        _fitness->insert({i, 0});
    }
}

void Genomes::Run(){
    BuildInitialPopulation();

    CalculateFitness();
    printf("Fitness complete");

    // Resort the _genome array so that high fitness is at the beginning
    SortFitness();

    CrossBreed();
}

void Genomes::BuildInitialPopulation() {
    auto random = std::uniform_int_distribution<uint64_t> (0, UINT64_MAX);
    for (int i=0;i<_populationCount;i++){
        _genomes[i] = _genomeGenerator(random(_rng));
    }
}

void Genomes::SortFitness(){
    // Flip the dictionary to be keyed by fitness then genome index
    // then add them in order back onto the array
    auto invertedFitness = std::make_unique<std::multimap<Fitness,GenomeIndex>>();
    for (GenomeIndex i=0;i<_populationCount;i++){
        invertedFitness->emplace(_fitness->at(i), i);
    }

    int index = _populationCount -1;
    std::for_each(invertedFitness->begin(), invertedFitness->end(), [&](const auto& n) {
        if (index < 0){
            throw std::exception("Index ended up at " + index);
        }
        _genomes[index--] = n.second;
    });
}

void Genomes::CrossBreed(){



    // Select two random cut points, transform into two bit masks
    // one for each parent.
    int cut1 = _randomCutPoint(_rng);
    int cut2 = cut1;
    while (cut1 == cut2){
        cut2 = _randomCutPoint(_rng);
    }

    //_crossbreeder->Crossbreed()
    throw std::exception("Not implemented");
}

void Genomes::CalculateFitness() {
    const int threadCount = 10;
    std::thread threads[threadCount];

    // Calculate fitness for each genome
    for (int i = 0; i < threadCount; i++) {
        threads[i] = std::thread(FitnessThread,
                                 i,
                                 _populationCount,
                                 _fitnessTest,
                                 _genomes);
    }

    for (int i = 0; i < threadCount; i++) {
        threads[i].join();
    }
}

void Genomes::FitnessThread(int threadNumber,
                            int populationCount,
                            std::function<Fitness(Genome)> fitnessTest,
                            std::shared_ptr<Genome[]> genomes){
    // use CurrentFitnessIndex to keep going until queue is empty;
    int myIndex = 0;
    while (myIndex < populationCount){
        myIndex = CurrentFitnessIndex++;
        if (myIndex >= populationCount){
            return;
        }
        Genome fitness = fitnessTest(genomes[myIndex]);
        // calculate fitness for _genomes[myIndex], store in _fitness
        // setting in _genomes may not be thread-safe and may require synchronization
        // consider setting into an array which should be safe and then processing the array afterwards
        genomes[myIndex] = fitness;
    }
}

// Synchronization of index across CalculateFitness' threads
std::atomic<int> Genomes::CurrentFitnessIndex = 0;
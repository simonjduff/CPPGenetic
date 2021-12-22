//
// Created by Simon Duff on 18/12/2021.
//

#include "Genomes.h"

Genomes::Genomes(std::shared_ptr<Crossbreeder> crossbreeder,
                 std::function<Genome(uint64_t)> genomeGenerator,
                 std::function<Fitness(Genome)> fitnessTest,
                 int populationCount){
    _populationCount = populationCount;
    _genomes = std::make_unique<Genome[]>(populationCount);
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

void Genomes::BuildInitialPopulation() {
    auto random = std::uniform_int_distribution<uint64_t> (0, UINT64_MAX);
    for (int i=0;i<_populationCount;i++){
        _genomes[i] = _genomeGenerator(random(_rng));
    }
}

void Genomes::FitnessThread(){
    // use _currentFitnessIndex to keep going until queue is empty;
    int myIndex = 0;
    while (myIndex < _populationCount){
        myIndex = _currentFitnessIndex++;

        // calculate fitness for _genomes[myIndex], store in _fitness
        // setting in _genomes may not be thread-safe and may require synchronization
        // consider setting into an array which should be safe and then processing the array afterwards
    }
}

void Genomes::SortFitness(){
    auto invertedFitness = std::make_unique<std::multimap<Fitness,GenomeIndex>>();
    for (GenomeIndex i=0;i<_populationCount;i++){
        invertedFitness->emplace(_fitness->at(i), i);
    }
}

void Genomes::CrossBreed(){
    // Select two random cut points, transform into two bit masks
    // one for each parent.
    int cut1 = _randomCutPoint(_rng);
    int cut2 = cut1;
    while (cut1 == cut2){
        cut2 = _randomCutPoint(_rng);
    }

    int lower = cut1, higher = cut2;
    if (cut1 > cut2){
        lower = cut2;
        higher = cut1;
    }
}

void Genomes::Run(){
    BuildInitialPopulation();
}
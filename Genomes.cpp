//
// Created by Simon Duff on 18/12/2021.
//

#include "Genomes.h"

Genomes::Genomes(int genomeSize, int populationCount){
    _genomeSize = genomeSize;
    _populationCount = populationCount;
    _genomes = std::make_unique<Genome[]>(genomeSize * populationCount);
    _fitness = std::make_unique<std::map<GenomeIndex,Fitness>>();
    std::mt19937 _rng(time(NULL));
    _randomGenomeIndex = std::uniform_int_distribution<int> (0, _populationCount - 1);
    // This needs to actually take into account the number of bits, not the number of int64s.
    _randomCutPoint = std::uniform_int_distribution<int> (0, _genomeSize * 64);


    for (int i=0;i<populationCount;i++){
        _fitness->insert({i, 0});
    }
}

void Genomes::setGenome(int index, Genome genome[]){
    for (int i=0;i<_genomeSize;i++){
        _genomes[(index * _genomeSize) + i] = genome[i];
    }
}

Genome* Genomes::getGenome(int index){
    return &_genomes[index * _genomeSize];
}

void Genomes::fitnessThread(){
    // use _currentFitnessIndex to keep going until queue is empty;
    int myIndex = 0;
    while (myIndex < _populationCount){
        myIndex = _currentFitnessIndex++;

        // calculate fitness for _genomes[myIndex], store in _fitness
        // setting in _genomes may not be thread-safe and may require synchronization
        // consider setting into an array which should be safe and then processing the array afterwards
    }
}

void Genomes::sortFitness(){
    auto invertedFitness = std::make_unique<std::multimap<Fitness,GenomeIndex>>();
    for (GenomeIndex i=0;i<_populationCount;i++){
        invertedFitness->emplace(_fitness->at(i), i);
    }
}

void Genomes::crossBreed(){
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
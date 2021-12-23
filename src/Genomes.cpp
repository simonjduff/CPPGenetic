//
// Created by Simon Duff on 18/12/2021.
//

#include <thread>
#include <mutex>
#include "Genomes.h"

Genomes::Genomes(std::shared_ptr<Crossbreeder> crossbreeder,
                 std::function<Genome(uint64_t)> genomeGenerator,
                 std::function<Fitness(Genome)> fitnessTest,
                 int populationCount){
    _populationCount = populationCount;
    _genomes = std::make_shared<Genome[]>(populationCount);
    _fitness = std::make_shared<std::map<Genome,Fitness>>();
    _historicalFitness = std::make_shared<std::map<Genome,Fitness>>();
    std::mt19937 _rng(time(NULL));
    _randomGenomeIndex = std::uniform_int_distribution<int> (0, _populationCount - 1);
    _randomCutPoint = std::uniform_int_distribution<int> (0, 63);
    _numberToCull = (_cullPercentage / 100.0) * _populationCount;
    _aliveIndex = std::uniform_int_distribution<int> (0, _populationCount - _numberToCull);
    _genomeSeed = std::uniform_int_distribution<uint64_t> (0, UINT64_MAX);
    _crossbreeder = crossbreeder;
    _fitnessTest = fitnessTest;
    _genomeGenerator = genomeGenerator;

    for (int i=0;i<populationCount;i++){
        _fitness->insert({i, 0});
    }
}

void Genomes::Run(){
    BuildInitialPopulation();

    Fitness bestFitness = 0;
    int sameFitnessCounter = 0;
    int generationCounter = 0;

    while (sameFitnessCounter < 100) {
        CalculateFitness();

        // Resort the _genome array so that high fitness is at the beginning
        SortFitness();
        sameFitnessCounter = bestFitness == _fitness->at(_genomes[0]) ? sameFitnessCounter + 1 : 0;
        bestFitness = _fitness->at(_genomes[0]);

        printf("Generation %d Best fitness %llu %f\n", generationCounter++, _genomes[0], bestFitness);

        CrossBreed();

        Mutate();
    }
}

void Genomes::BuildInitialPopulation() {
    for (int i=0;i<_populationCount;i++){
        _genomes[i] = _genomeGenerator(_genomeSeed(_rng));
    }
}

void Genomes::SortFitness(){
    // Flip the dictionary to be keyed by fitness then genome
    // then add them in order back onto the array
    auto invertedFitness = std::make_unique<std::multimap<Fitness,Genome>>();
    for(int i=0;i<_populationCount;i++){
        if (!_fitness->contains(_genomes[i])){
            printf("Genome %d %llu not found\n", i, _genomes[i]);
        }
        invertedFitness->emplace(_fitness->at(_genomes[i]), _genomes[i]);
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
    for (int i=0; i < _numberToCull; i++){
        int secondParentIndex = _aliveIndex(_rng);

        auto cuts = std::array<int,2>();
        // Select two random cut points, transform into two bit masks
        // one for each parent.
        cuts[0] = _randomCutPoint(_rng);
        cuts[1] = cuts[0];
        while (cuts[0] == cuts[1]){
            cuts[1] = _randomCutPoint(_rng);
        }

        _genomes[_populationCount-1-i] = _crossbreeder->Crossbreed(_genomes[i], _genomes[secondParentIndex], cuts);
    }
}

void Genomes::CalculateFitness() {
    _fitness->clear();

    CurrentFitnessIndex = 0;
    const int threadCount = 10;
    std::thread threads[threadCount];

    // Calculate fitness for each genome
    for (int i = 0; i < threadCount; i++) {
        threads[i] = std::thread(FitnessThread,
                                 i,
                                 _populationCount,
                                 _fitnessTest,
                                 _genomes,
                                 _fitness,
                                 _historicalFitness);
    }

    for (int i = 0; i < threadCount; i++) {
        threads[i].join();
    }
}

void Genomes::Mutate() {
    int mutationCount = (_mutationPercentage / 100.0) * _populationCount;
    for (int i=0; i < mutationCount; i++){
        auto index = _randomGenomeIndex(_rng);
        _genomes[index] = _genomeGenerator(_genomeSeed(_rng));
    }
}

void Genomes::FitnessThread(int threadNumber,
                            int populationCount,
                            std::function<Fitness(Genome)> fitnessTest,
                            std::shared_ptr<Genome[]> genomes,
                            std::shared_ptr<std::map<Genome,Fitness>> fitness,
                            std::shared_ptr<std::map<Genome,Fitness>> historicalFitness){
    static std::mutex mtx;

    // TODO Could improve mutex locking here. Each thread could have a buffer and only lock the output map when it needs to write

    // use CurrentFitnessIndex to keep going until queue is empty;
    int myIndex = 0;
    while (myIndex < populationCount){
        myIndex = CurrentFitnessIndex++;
        if (myIndex >= populationCount){
            return;
        }

        Genome currentGenome = genomes[myIndex];
        Fitness fitnessScore;
        if (!historicalFitness->contains(currentGenome)){
            fitnessScore = fitnessTest(currentGenome);
            // calculate fitness for _genomes[myIndex], store in _fitness
            // setting in _genomes may not be thread-safe and may require synchronization
            // consider setting into an array which should be safe and then processing the array afterwards
            mtx.lock();
            historicalFitness->insert_or_assign(currentGenome, fitnessScore);
            mtx.unlock();
        } else {
            mtx.lock();
            fitnessScore = historicalFitness->at(currentGenome);
            mtx.unlock();
        }
        mtx.lock();
        fitness->insert_or_assign(currentGenome, fitnessScore);
        mtx.unlock();
    }
}

// Synchronization of index across CalculateFitness' threads
std::atomic<int> Genomes::CurrentFitnessIndex = 0;
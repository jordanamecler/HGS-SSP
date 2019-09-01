/**
 * @file LocalSearch.cpp
 *
 * Implements LocalSearch class methods
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */

#include "LocalSearch.h"
#include "Individual.h"

bool LocalSearch::searchNeighborhood(unsigned int i) {
    if (i == 1) return twoOpt();
    if (i == 2) return relocate();
    else return swap();
}

void LocalSearch::runSearchTotal() {
    // For each local search procedure, the order of
    // the search is shuffled and it stops when cant
    // find a better solution using this procedure
    // in an entire loop in the indices

    bool foundBetter;

    while (true) {
        foundBetter = false;
        shuffleIndices();
        shuffleMoves();
        for (unsigned int i = 1; i <= 3 && !foundBetter; i++) {
            foundBetter = searchNeighborhood(i);
        }
        if (!foundBetter) break;
    }
}

bool LocalSearch::relocate() {
    // Relocate method: tries to relocate an element
    // to all the other possible positions in the vector

    unsigned int modifiedCost;
    bool foundBetter = false;
    double currZeroBlocks = individual->solutionCost.zeroBlocks;
    double newSolutionZeroBlocks;

    for (const vector<unsigned int> &pos : parameters->orderLS) {

        unsigned int iValue = individual->chromosome[pos[0]];

        individual->chromosome.erase(individual->chromosome.begin() + pos[0]);
        individual->chromosome.insert(individual->chromosome.begin() + pos[1], iValue);

        modifiedCost = individual->calcCost(-1);
        if (modifiedCost <= individual->solutionCost.evaluation) {
            newSolutionZeroBlocks = individual->calcZeroBlocks();
            if (modifiedCost < individual->solutionCost.evaluation || newSolutionZeroBlocks < currZeroBlocks - 0.0001) {
                if (modifiedCost < individual->solutionCost.evaluation)
                    parameters->improvesPrimary++;
                else
                    parameters->improvesSecondary++;
                individual->solutionCost.evaluation = modifiedCost;
                currZeroBlocks = newSolutionZeroBlocks;
                individual->solutionCost.zeroBlocks = currZeroBlocks;
                foundBetter = true;
                continue;
            }
        }

        individual->chromosome.erase(individual->chromosome.begin() + pos[1]);
        individual->chromosome.insert(individual->chromosome.begin() + pos[0], iValue);
    }
    return foundBetter;
}

bool LocalSearch::swap() {
    // Swap method: tries to swap every combination of
    // two elements of the vector

    unsigned int modifiedCost;
    bool foundBetter = false;
    unsigned int temp;
    double currZeroBlocks = individual->solutionCost.zeroBlocks;
    double newSolutionZeroBlocks;

    for (const vector<unsigned int> &pos : parameters->orderLS) {

        temp = individual->chromosome[pos[0]];
        individual->chromosome[pos[0]] = individual->chromosome[pos[1]];
        individual->chromosome[pos[1]] = temp;

        modifiedCost = individual->calcCost(-1);
        if (modifiedCost <= individual->solutionCost.evaluation) {
            newSolutionZeroBlocks = individual->calcZeroBlocks();
            if (modifiedCost < individual->solutionCost.evaluation || newSolutionZeroBlocks < currZeroBlocks - 0.0001) {
                if (modifiedCost < individual->solutionCost.evaluation)
                    parameters->improvesPrimary++;
                else
                    parameters->improvesSecondary++;
                individual->solutionCost.evaluation = modifiedCost;
                currZeroBlocks = newSolutionZeroBlocks;
                individual->solutionCost.zeroBlocks = currZeroBlocks;
                foundBetter = true;
                continue;
            }
        }

        individual->chromosome[pos[1]] = individual->chromosome[pos[0]];
        individual->chromosome[pos[0]] = temp;
    }
    return foundBetter;
}

bool LocalSearch::twoOpt() {
    // Two opt method: invert a sequence of the vector

    unsigned int modifiedCost;
    bool foundBetter = false;
    double currZeroBlocks = individual->solutionCost.zeroBlocks;
    double newSolutionZeroBlocks;

    for (const vector<unsigned int> &pos : parameters->orderLS) {
        parameters->modifiedSolution.clear();
        parameters->tempSolution.clear();
        copy(individual->chromosome.begin(), individual->chromosome.begin() + pos[0],
             back_inserter(parameters->modifiedSolution));
        copy(individual->chromosome.begin() + pos[0], individual->chromosome.begin() + pos[1] + 1,
             back_inserter(parameters->tempSolution));
        reverse(parameters->tempSolution.begin(), parameters->tempSolution.end());
        parameters->modifiedSolution.insert(parameters->modifiedSolution.end(),
                                        parameters->tempSolution.begin(),
                                        parameters->tempSolution.end());
        parameters->modifiedSolution.insert(parameters->modifiedSolution.end(),
                                        individual->chromosome.begin() + pos[1] + 1, individual->chromosome.end());

        tempIndiv->chromosome = parameters->modifiedSolution;
        modifiedCost = tempIndiv->calcCost(-1);

        if (modifiedCost < individual->solutionCost.evaluation) {
            individual->solutionCost.evaluation = modifiedCost;
            individual->chromosome = parameters->modifiedSolution;
            currZeroBlocks = individual->calcZeroBlocks();
            individual->solutionCost.zeroBlocks = currZeroBlocks;
            parameters->improvesPrimary++;
            foundBetter = true;
        }
        else if (modifiedCost == individual->solutionCost.evaluation) {
            newSolutionZeroBlocks = tempIndiv->calcZeroBlocks();
            if (newSolutionZeroBlocks < currZeroBlocks - 0.0001) {
                individual->solutionCost.evaluation = modifiedCost;
                individual->chromosome = parameters->modifiedSolution;
                currZeroBlocks = newSolutionZeroBlocks;
                individual->solutionCost.zeroBlocks = currZeroBlocks;
                parameters->improvesSecondary++;
                foundBetter = true;
            }
        }
    }
    return foundBetter;
}

LocalSearch::LocalSearch() {
}

LocalSearch::LocalSearch(Parameters *parameters, Individual *individual) : parameters(parameters), individual(individual) {
    tempIndiv = new Individual(parameters);
    tempIndiv->recopyIndividual(tempIndiv, individual);
    runSearchTotal();
}

LocalSearch::~LocalSearch() {
    delete tempIndiv;
}

int genRandom(int i) {
    return std::rand() % i;
}

void LocalSearch::shuffleMoves() {
    random_shuffle(parameters->moves.begin(), parameters->moves.end(), genRandom);
}

void LocalSearch::shuffleIndices() {
    // Shuffling the jobs order vector
    random_shuffle(parameters->orderLS.begin(), parameters->orderLS.end(), genRandom);
}
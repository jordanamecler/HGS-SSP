/**
 * @file Individual.cpp
 *
 * Implements Individual class methods
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */

#include "Individual.h"

Individual::Individual(Parameters *parameters) : parameters(parameters) {

    age = 0;
    isFitnessComputed = false;

    // Start individual as permutation of jobs
    for (unsigned int i = 0; i < parameters->numJobs; i++) {
        chromosome.push_back(i);
        edgesIndividuals.push_back(0);
    }

    unsigned int temp, jj;
    // shuffling
    for (unsigned int i = 0; i <= (unsigned int)chromosome.size() - 1; i++) {
        jj = i + rand() % ((unsigned int)chromosome.size() - i);
        temp = chromosome[i];
        chromosome[i] = chromosome[jj];
        chromosome[jj] = temp;
    }

    solutionCost.evaluation = calcCost(-1);
    solutionCost.zeroBlocks = calcZeroBlocks();
}

Individual::~Individual() {}

unsigned int Individual::calcCost(int jump) {
    // This method implements the KTNS policy
    // (keep tools needed soonest)
    // It is a dynamic programming approach to calculate
    // the number of tool switches given a fixed order of
    // jobs in polynomial time

    // Fills L matrix (auxiliary structure used by KTNS)
    for (int i = (parameters->numJobs - 1); i >= 0; i--) {
        for (unsigned int j = 0; j < parameters->numTools; j++) {
            if (i != jump && parameters->jobsToolsMatrix[chromosome[i]][j] == 1) {
                parameters->L[j][i] = (unsigned int)i;
            }
            else if (i < (int)parameters->numJobs - 1) {
                parameters->L[j][i] = parameters->L[j][i + 1];
            }
            else {
                parameters->L[j][i] = parameters->numJobs;
            }
            parameters->used[j] = false;
        }
    }

    unsigned int switches = 0;
    unsigned int capacity = 0;
    unsigned int tool = 0;
    double minVal;

    // Fills auxiliary vector W_n that corresponds to the
    // matrix row at instant n
    for (unsigned int i = 0; i < parameters->numTools; i++) {
        if (parameters->L[i][0] == 0) {
            parameters->W_n[i] = 1;
            parameters->used[i] = true;
            capacity++;
        }
        else {
            parameters->W_n[i] = 0;
        }
    }

    while (capacity < parameters->maxCapacity) {
        minVal = numeric_limits<double>::infinity();
        for (unsigned int i = 0; i < parameters->numTools; i++) {
            if (!parameters->used[i] && (parameters->L[i][0] < minVal)) {
                tool = i;
                minVal = parameters->L[i][0];
            }
        }
        parameters->used[tool] = true;
        parameters->W_n[tool] = 1;
        capacity++;
    }

    parameters->loadedMatrix[0] = parameters->W_n;

    unsigned int maxVal;
    for (unsigned int n = 1; n < parameters->numJobs; n++) {
        for (unsigned int i = 0; i < parameters->numTools; i++) {
            if (parameters->W_n[i] != 1 && parameters->L[i][n] == n) {
                parameters->W_n[i] = 1;
                capacity++;
            }
        }
        while (capacity > parameters->maxCapacity) {
            maxVal = n;
            for (unsigned int i = 0; i < parameters->numTools; i++) {
                if (parameters->W_n[i] == 1 && parameters->L[i][n] > maxVal) {
                    tool = i;
                    maxVal = parameters->L[i][n];
                }
            }
            parameters->W_n[tool] = 0;
            capacity--;
            switches++;
        }
        parameters->loadedMatrix[n] = parameters->W_n;
    }
    return switches;
}

//unsigned int Individual::calcOneBlocks() {
//
//    unsigned int oneBlocks = 0;
//
//    for (unsigned int i = 0; i < parameters->numTools; i++) {
//        if (parameters->jobsToolsMatrix[chromosome[0]][i] == 1) {
//            oneBlocks++;
//        }
//        for (unsigned int j = 1; j < parameters->numJobs; j++) {
//            if (parameters->jobsToolsMatrix[chromosome[j - 1]][i] == 0 && parameters->jobsToolsMatrix[chromosome[j]][i] == 1) {
//                oneBlocks++;
//            }
//        }
//    }
//    return oneBlocks;
//}

double Individual::calcZeroBlocks() {
    // This method calculates the second (auxiliary) objective
    // used in the local search procedures:
    // The sum of the square roots of zero block sizes of the solution

    double zeroBlocks = 0;

    for (unsigned int i = 0; i < parameters->numTools; i++) {
        double sizeOfBlock = 0;
        for (unsigned int j = 1; j < parameters->numJobs; j++) {
            if ((parameters->loadedMatrix[j - 1][i] == 1 || sizeOfBlock > 0) && parameters->loadedMatrix[j][i] == 0) {
                sizeOfBlock++;
            }
            if (sizeOfBlock > 0 && parameters->loadedMatrix[j][i] == 1) {
                zeroBlocks += sqrt(sizeOfBlock);
                sizeOfBlock = 0;
            }
        }
        zeroBlocks += sqrt(sizeOfBlock);
    }

    return zeroBlocks;
}

void Individual::recopyIndividual(Individual *destination, Individual *source) {

    destination->chromosome = source->chromosome;
    destination->solutionCost.evaluation = source->solutionCost.evaluation;
    destination->solutionCost.zeroBlocks = source->solutionCost.zeroBlocks;
    destination->closest = source->closest;
    destination->isFitnessComputed = source->isFitnessComputed;
    destination->age = 0;
}

unsigned int Individual::distance(Individual *indiv) {
    // This method computed the edges distance between two solutions
    // If an element of solution 1 has a different neighbor (behind
    // or ahead) from the same element of solution 2, then the distance
    // is incremented by one

    unsigned int dist = 0;
    for (unsigned int i = 0; i < chromosome.size() - 2; i++) {
        edgesIndividuals[chromosome[i]] = (int) chromosome[i + 1];
    }
    for (unsigned int i = 0; i < indiv->chromosome.size() - 2; i++) {
        if (edgesIndividuals[indiv->chromosome[i]] != indiv->chromosome[i + 1] && edgesIndividuals[indiv->chromosome[i + 1]] != indiv->chromosome[i]) {
            dist++;
        }
    }
    return dist;
}

void Individual::addClose(Individual *indiv) {
    // Add an individual in the structure of proximity
    list<ProxData>::iterator it;
    ProxData data;
    data.individual = indiv;
    data.dist = distance(indiv);

    if (closest.empty())
        closest.push_back(data);
    else {
        it = closest.begin();
        while (it != closest.end() && it->dist < data.dist)
            ++it;
        closest.insert(it, data);
    }
}

void Individual::removeClose(Individual *indiv) {
    // Remove an individual in the structure of proximity
    list<ProxData>::iterator last = closest.end();
    for (list<ProxData>::iterator first = closest.begin(); first != last;)
        if (first->individual == indiv)
            first = closest.erase(first);
        else
            ++first;
}

double Individual::distToClosests(int n) {
    // Compute the average distance with the n close elements
    double result = 0;
    double compte = 0;
    list<ProxData>::iterator it = closest.begin();

    for (int i = 0; i < n && it != closest.end(); i++) {
        result += it->dist;
        compte += 1.0;
        ++it;
    }
    return result / compte;
}
/**
 * @class Individual
 *
 * @brief Handle individual information
 *
 * Store individual (solution) information such as its chromosome,
 * cost, zero blocks and fitness.
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include <list>
#include <iostream>
#include "Parameters.h"
#include "LocalSearch.h"

using namespace std;

class LocalSearch;

/// Structure used to keep the cost of a solution
struct SolutionCost {

    // Cost of the solution
    unsigned int evaluation;

    // Sum of square root of size of zero blocks
    double zeroBlocks;

    // Constructor
    SolutionCost() {
        evaluation = 0;
        zeroBlocks = 0;
    }
};

/// Preliminary declaration, because proxData depends on Individual
class Individual;

/// Structure about the proximity of an Individual with regards to the others in the population
struct ProxData {
    // Individual
    Individual *individual;

    // Its distance to the others
    double dist;
};

class Individual
{
public:

    Parameters *parameters; ///< problem parameters

    int age; ///< age of individual

    double fitnessExt; ///< fitness of individual considering its cost and contribution to diversity

    float divRank; ///< rank of individual in terms of diversity

    float fitRank; ///< rank of individual in terms of cost

    SolutionCost solutionCost; ///< KTNS cost of solution

    vector<unsigned int> chromosome; ///< chromosome of individual stores a permutation of jobs

    vector<int> edgesIndividuals; ///< temporary structure to compute distance

    bool isFitnessComputed; ///< if fitness has been computed

    /**
     * Calculate distance (edges distance) to an individual.
     *
     * @param indiv individual to be compared with current
     *
     * @return distance
     */
    unsigned int distance(Individual *indiv);

    list<ProxData> closest; ///< Population individuals ranked by proximity

    /**
     * Add individual to proximity structure.
     *
     * @param indiv individual to be added
     */
    void addClose(Individual *indiv);

    /**
     * Remove individual from proximity structure.
     *
     * @param indiv individual to be removed.
     */
    void removeClose(Individual *indiv);

    /**
     * Calculate distance to n closest individuals
     *
     * @param n number of individuals to be considered
     *
     * @return distance
     */
    double distToClosests(int n);

    LocalSearch *localSearch; ///< structure to perform local search

    /**
     * Calculates the cost of the solution using KTNS
     * (keep tools needed soonest).
     *
     * @param jump position of job to skip
     *
     * @return value of solution cost
     */
    unsigned int calcCost(int jump);

    /**
     * Calculate the auxiliary objective used in local search:
     * sum of the square roots of the sizes of zero blocks in the solution.
     *
     * @return value of auxiliary objective
     */
    double calcZeroBlocks();

    /**
     * Copy one individual attributes to another.
     *
     * @param destination destination individual
     * @param source source individual
     */
    void recopyIndividual(Individual *destination, Individual *source);

    /**
     * Constructor initializes a random individual.
     *
     * @param parameters problem parameters
     */
    explicit Individual(Parameters *parameters);

    /// Destructor
    ~Individual();

};

#endif //INDIVIDUAL_H
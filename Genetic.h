/**
 * @class Genetic
 *
 * @brief Handle genetic algorithm
 *
 * Core of the genetic algorithm. Evolve population through
 * crossover operations until a maximum number of iterations
 * without improvement is reached.
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */

#ifndef GENETIC_H
#define GENETIC_H

#include "Population.h"
#include "Parameters.h"
#include "Individual.h"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>

using namespace std;

class Genetic
{
private:

    int nbIterWithoutImprov; ///< number of iterations without improvement

    int nbIter; ///< number of iterations

public:

    clock_t ticks; ///< maximum time

    bool traces; ///< if should print traces

    Population *population; ///< population structure

    Individual *offspring; ///< temporary structure for crossover childs

    Individual *trainer; ///< temporary structure for local search

    Parameters *parameters; ///< problem parameters

    /**
     * Run the genetic algorithm until a number of maximum iterations
     * without improvement is reached.
     *
     * @param maxIterWithoutImprov
     */
    void evolve(int maxIterWithoutImprov);

    /**
     * Order crossover (OX) works by selecting a part of one parent
     * and copying it to the child, and then go through the second
     * parent sequentially filling the child unfilled positions with
     * its values.
     *
     * @param parent1 first parent
     * @param parent2 second parent
     */
    void crossoverOX(Individual *parent1, Individual *parent2);

    /**
     * Constructor
     *
     * @param parameters problem parameters
     * @param population population structure
     * @param ticks clock info
     * @param traces if should print traces
     */
    Genetic(Parameters *parameters, Population *population, clock_t ticks, bool traces);

    /// Destructor
    ~Genetic();
};

#endif //GENETIC_H
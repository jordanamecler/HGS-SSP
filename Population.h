/**
 * @class Population
 *
 * @brief Handle population events
 *
 * Population management. Insert and remove individuals
 * based on fitness (cost and diversity) criteria.
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */

#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "Individual.h"

using namespace std;

/// Structure to manage the population
struct SubPopulation {

    vector<Individual*> individuals; ///< individuals in the population

    int numberIndividuals; ///< number of individuals in the population
};

class Population {

private:

//    unsigned int maxClones;

    /**
     * Education procedure (calls local search) for an individual.
     *
     * @param indiv individual to be educated
     */
    void education(Individual *indiv);

    /**
     * Inserts individual in the population.
     *
     * @param subPop structure of the population
     * @param indiv individual to be inserted
     *
     * @return position where individual was inserted
     */
    int placeIndividual(SubPopulation *subPop, Individual *indiv);

public:

    Parameters *parameters; ///< holds problem parameters

    Individual *trainer; ///< structure to instantiate only one individual for local search procedures

    SubPopulation *subPopulation; ///< structure to handle the population

    /**
     * Check if exists individual with same fitness in the population.
     *
     * @param subPop structure of the population
     * @param indiv individual to check
     *
     * @return true if exists, false otherwise
     */
    bool fitExist(SubPopulation *subPop, Individual *indiv);

    /**
     * Compute biased fitness of individuals in the population
     * based on their cost and contribution to diversity.
     *
     * @param subPop structure of the population
     */
    void evalExtFit(SubPopulation *subPop);

    /**
     * Add individual in the population and keep survivors
     * in case of reaching maximum size.
     *
     * @param indiv individual to be added
     *
     * @return position of individual
     */
    int addIndividual(Individual *indiv);

    /**
     * Remove individual from the population and from
     * the proximity structures.
     *
     * @param subPop the population structure
     * @param p position of individual
     */
    void removeIndividual(SubPopulation *subPop, int p);

    /**
     * Select an individual to be removed from the population
     *
     * @param subPop the population structure
     *
     * @return position of individual
     */
    int selectToRemove(SubPopulation *subPop);

    /**
     * Update table of distance for the new individual
     * (distance from this individual to the rest of the population).
     *
     * @param subPop the population structure
     * @param indiv the new individual
     */
    void updateProximity(SubPopulation *subPop, Individual *indiv);

    /**
     * Diversification removes a large part of the
     * population and creates new individuals.
     */
    void diversify();

    /**
     * Binary tournament takes two individuals at random
     * and keeps the one with best fitness.
     *
     * @return individual
     */
    Individual *getIndividualBinT();

    /**
     * Select individual with best fitness
     *
     * @return best individual
     */
    Individual *getBestIndividual();

    /// Update individuals age (increase by one)
    void updateAge();

    void calcJobsDistance(SubPopulation *subPop, Parameters *parameters);

    /**
     * Constructor initializes population by
     * creating new individuals and educating
     * them through local search procedures
     *
     * @param parameters the problem parameters
     */
    Population(Parameters *parameters);

    /// Destructor
    ~Population();
};

#endif //POPULATION_H
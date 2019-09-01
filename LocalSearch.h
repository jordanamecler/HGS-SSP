/**
 * @class LocalSearch
 *
 * @brief Local search procedures
 *
 * Perform local search procedures such as
 * relocate, swap and 2-opt.
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */

#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>
#include "Parameters.h"

using namespace std;

class Individual;

// Local Search class
class LocalSearch
{
private:

    /// Searches the neighborhood represented by index i
    bool searchNeighborhood(unsigned int i);

    /// Shuffle indices for random order in local search methods
    void shuffleMoves();

    /// Shuffle indices for random order in local search
    void shuffleIndices();

    /// Relocate local search
    bool relocate();

    /// Swap local search
    bool swap();

    /// 2-opt local search
    bool twoOpt();

public:

    Parameters *parameters; ///< problem parameters

    Individual *individual; ///< individual to perform local search

    Individual *tempIndiv; ///< temporary structure for local search

    /// Run complete local search
    void runSearchTotal();

    /// Constructor
    LocalSearch();

    /**
     * Constructor initializes data structures
     *
     * @param parameters problem parameters
     * @param individual individual to perform local search
     */
    LocalSearch(Parameters * parameters, Individual *individual);

    /// Destructor
    ~LocalSearch();
};

#endif //LOCALSEARCH_H
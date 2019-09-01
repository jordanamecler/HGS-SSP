/**
 * @class CommandLine
 *
 * @brief Read parameters from command line
 *
 *  Read arguments from command line, check if they are valid,
 *  store and provide access to them.
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <iostream>
#include <string>
using namespace std;

class CommandLine
{
private:

    bool commandOk; ///< if command line arguments are valid

    int cpuTime; ///< time for execution allowed

    int seed; ///< seed for random

    string instancesPaths; ///< set of instances path

    string instancesNames; ///< set of instances prefix

    string solutionPath; ///< solution file path

    unsigned int populationSize; ///< minimum population size

    unsigned int maxPopulationSize; ///< maximum subpopulation size

    unsigned int numberElite; ///< number of elite solutions considered in fitness

    unsigned int numberCloseIndividuals; ///< number of individuals considered in distance measures

    unsigned int maxDiversify; ///< maximum number of iterations without improvement resulting in diversification

    unsigned int runs; ///< number of runs of the algorithm to generate average results

public:

    /**
     * Check if command line arguments are valid.
     *
     * @return true if arguments from command line are valid, false otherwise
     */
    bool isValid();

    /**
     *
     * @return maximum cpu time accepted
     */
    int getCpuTime();
    /**
     *
     * @return random seed
     */
    int getSeed();
    /**
     *
     * @return set of instances path
     */
    string getInstancesPaths();
    /**
     *
     * @return set of instances prefix
     */
    string getInstancesNames();
    /**
     *
     * @return solution file path
     */
    string getSolutionPath();
    /**
     *
     * @return minimum population size
     */
    unsigned int getPopulationSize();
    /**
     *
     * @return maximum subpopulation size
     */
    unsigned int getMaxPopulationSize();
    /**
     *
     * @return number of elite individuals considered for fitness
     */
    unsigned int getNumberElite();
    /**
     *
     * @return number of close individuals considered for distance measures
     */
    unsigned int getNumberCloseIndividuals();
    /**
     *
     * @return maximum number of iterations without improvement resulting in diversification
     */
    unsigned int getMaxDiversify();
//    unsigned int getRuns();

     /**
      * Constructor receives command line arguments
      *
      * @param argc argc from command line
      * @param argv argv form command line
      */
    CommandLine(int argc, char* argv[]);

    /// Destructor.
    ~CommandLine();
};

#endif //COMMANDLINE_H
/**
 * @file CommandLine.cpp
 *
 * Implements CommandLine class methods
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */

#include "CommandLine.h"

CommandLine::CommandLine(int argc, char **argv) {

    // Check number of arguments
    if (argc < 5) {
//        cout << "Wrong command line" << endl;
        commandOk = false;
        return;
    }

    seed = 0;

    instancesPaths = string(argv[1]);
    instancesNames = string(argv[2]);
    solutionPath = string(argv[3]);
    seed = stoi(argv[4]);
//    populationSize = (unsigned int) stoi(argv[5]);
//    maxPopulationSize = (unsigned int) stoi(argv[6]);
//    numberElite = (unsigned int) stoi(argv[7]);
//    numberCloseIndividuals = (unsigned int) stoi(argv[8]);
//    maxDiversify = (unsigned int) stoi(argv[9]);

//    runs = (unsigned int)stoi(argv[10]);
//    if (runs <= 0) {
//        cout << "Number of executions must be > 0" << endl;
//        commandOk = false;
//        return;
//    }

    commandOk = true;
}

CommandLine::~CommandLine() {};

bool CommandLine::isValid() {
    return commandOk;
}

int CommandLine::getCpuTime() {
    return cpuTime;
}

int CommandLine::getSeed() {
    return seed;
}

string CommandLine::getInstancesPaths() {
    return instancesPaths;
}

string CommandLine::getInstancesNames() {
    return instancesNames;
}

string CommandLine::getSolutionPath() {
    return solutionPath;
}

unsigned int CommandLine::getPopulationSize() {
    return populationSize;
}

unsigned int CommandLine::getMaxPopulationSize() {
    return maxPopulationSize;
}

unsigned int CommandLine::getNumberElite() {
    return numberElite;
}

unsigned int CommandLine::getNumberCloseIndividuals() {
    return numberCloseIndividuals;
}

unsigned int CommandLine::getMaxDiversify() {
    return maxDiversify;
}

//unsigned int CommandLine::getRuns() {
//    return runs;
//}
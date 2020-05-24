/**
 * @file Parameters.cpp
 *
 * Implements Parameters class methods
 *
 * @author Jordana Mecler
 *
 * Contact: jmecler@inf.puc-rio.br
 *
 */

//#include <Windows.h>
#include <iterator>
#include <glob.h>
#include "Parameters.h"

void Parameters::setMethodParams() {
    populationSize = 20;
    maxPopulationSize = 40;
    numberElite = 10;
    numberCloseIndividuals = 3;
    maxDiversify = 1000;
    terminate = false;
}

void Parameters::setAuxiliaryParams() {
    vector<vector<unsigned int> > L(numTools, vector<unsigned int>(numJobs));
    vector<unsigned int> W_n(numTools);
    vector<bool> used(numTools);
    vector<bool> positionsOffspring(numJobs);
    vector<bool> improvedRemoving(numJobs);
//    vector<vector<unsigned int>> jobsDistance(numJobs, vector<unsigned int>(numJobs));
    vector<vector<unsigned int> > loadedMatrix(numJobs, vector<unsigned int>(numTools));
    this->L = L;
    this->W_n = W_n;
    this->used = used;
    this->positionsOffspring = positionsOffspring;
//    this->improvedRemoving = improvedRemoving;
    this->loadedMatrix = loadedMatrix;

    this->moves = {1, 2, 3};
    if (this->orderLS.empty()) {
        for (unsigned int i = 0; i < numJobs; i++) {
            for (unsigned int j = i + 1; j < numJobs; j++) {
                this->orderLS.push_back({i,j});
            }
        }
    }
}

void Parameters::getFiles() {
    // Get the set of instances given the path and prefix determined

    vector<string> prefixList;
    if (instancesNames.find('L') != string::npos) {
        string val;
        stringstream prefixStream;
        prefixStream.str(instancesNames);
        while (getline(prefixStream, val, '-')) {
            val.append("-");
            prefixList.push_back(val);
        }
    }
    else {
        prefixList.push_back(instancesNames);
    }

    for (const string &item : prefixList) {
        string pattern(instancesPaths);
        pattern.append("/").append(item).append("*");
//        WIN32_FIND_DATAA data;
//        HANDLE hFind;
//        cout << pattern << endl;
//        if ((hFind = FindFirstFileA(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
//            do {
//                string file = instancesPaths;
//                file.append("\\").append(data.cFileName);
//                files.push_back(file);
//            } while (FindNextFileA(hFind, &data) != 0);
//            FindClose(hFind);
//        }
        glob_t globResult;
        glob(pattern.c_str(), GLOB_TILDE, nullptr, &globResult);
        for (unsigned int i = 0; i < globResult.gl_pathc; ++i) {
            files.push_back(string(globResult.gl_pathv[i]));
        }
        globfree(&globResult);
    }

    if (files.empty()) {
        cout << "No files found matching the specified prefix. Exiting." << endl;
    }
}

void Parameters::readFile(const string &file) {
    // Read instance file

    ifstream inFile(file);

    if (inFile.good()) {
        string sLine;
        getline(inFile, sLine);
        if (file.find("Yanasse") != string::npos) {
            istringstream iss(sLine);
            vector<string> tokens{(istream_iterator<string>(iss)), istream_iterator<string>() };
            numJobs = (unsigned int)stoi(tokens[0]);
            numTools = (unsigned int)stoi(tokens[1]);
            maxCapacity = (unsigned int)stoi(tokens[2]);
        }
        else {
            numJobs = (unsigned int)stoi(sLine);
            getline(inFile, sLine);
            numTools = (unsigned int)stoi(sLine);
            getline(inFile, sLine);
            maxCapacity = (unsigned int)stoi(sLine);
        }

        unsigned int j = 0;
        vector<vector<unsigned int> > lines(numJobs, vector<unsigned int>(numTools, 0));
        while (getline(inFile, sLine)) {
            istringstream iss(sLine);
            vector<string> tokens {(istream_iterator<string>(iss)), istream_iterator<string>() };
            for (unsigned int i = 0; i < tokens.size(); i++) {
                lines[i][j] = (unsigned int)stoi(tokens[i]);
            }
            j++;
        }
        jobsToolsMatrix = lines;
    }
    inFile.close();
}

Parameters::Parameters(int seed, string instancesPaths, string instancesNames, string solutionPath, unsigned int populationSize, unsigned int maxPopulationSize, unsigned int numberElite, unsigned int numberCloseIndividuals, unsigned int maxDiversify) {
    this->instancesPaths = instancesPaths;
    this->instancesNames = instancesNames;
    this->solutionPath = solutionPath;
//    this->populationSize = populationSize;
//    this->maxPopulationSize = maxPopulationSize;
//    this->numberElite = numberElite;
//    this->numberCloseIndividuals = numberCloseIndividuals;
//    this->maxDiversify = maxDiversify;
    this->seed = seed;
    if (seed == 0) // using the time to generate a seed when seed = 0
        srand((unsigned int)time(nullptr));
    else
        srand((unsigned int) this->seed);

    getFiles();

    // Setting the method parameters
    setMethodParams();

    setAuxiliaryParams();
}

Parameters::~Parameters() {}
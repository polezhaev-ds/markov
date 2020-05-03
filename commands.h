//
// Created by datas on 02.05.2020.
//

#ifndef MARKOV_COMMANDS_H
#define MARKOV_COMMANDS_H

#include "external/cxxopts.hpp"
#include <string>

void printUsageExamples();

bool checkAndPrintProvidedOptionForIgnorance(const cxxopts::ParseResult& parseResult, const std::string& optionPair);

void checkAndPrintProvidedOptionsVectorForIgnorance(const cxxopts::ParseResult& parseResult,
        const std::vector<std::string>& optionPairs);

void printOptionValuesForDownloadAllFilesCommand(const std::string& directoryNameToStoreDownloadedFiles,
        const std::string& urlListFileName, bool deleteAllStoredFiles);

void printOptionValuesForTrainMarkovGeneratorCommand(const std::string& directoryNameToStoreDownloadedFiles,
        std::size_t markovGeneratorOrder, const std::string& markovGeneratorStateFileName, bool useIncrementalTraining);

void printOptionValuesForDownloadAllFilesAndTrainMarkovGeneratorCommand(const std::string& directoryNameToStoreDownloadedFiles,
        const std::string& urlListFileName, bool deleteAllStoredFiles, std::size_t markovGeneratorOrder,
        const std::string& markovGeneratorStateFileName, bool useIncrementalTraining);


void downloadAllFiles(const std::string& directoryNameToStoreDownloadedFiles, const std::string& urlListFileName,
        bool deleteAllStoredFiles);

void trainMarkovGeneratorOnAllFiles(const std::string& directoryNameToStoreDownloadedFiles,
        std::size_t markovGeneratorOrder, const std::string& markovGeneratorStateFileName, bool useIncrementalTraining);

void downloadAllFilesAndTrainMarkovGenerator(const std::string& directoryNameToStoreDownloadedFiles,
        const std::string& urlListFileName, bool deleteAllStoredFiles, std::size_t markovGeneratorOrder,
        const std::string& markovGeneratorStateFileName, bool useIncrementalTraining);

void generateTextUsingMarkovGenerator(const std::string& markovGeneratorStateFileName, std::size_t generatedTextLength,
    const std::string& startingPhrase);

void parseAndProcessCommand(int argc, char* argv[]);

#endif //MARKOV_COMMANDS_H

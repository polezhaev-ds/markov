//
// Created by datas on 02.05.2020.
//

#include "commands.h"
#include "parse_file.h"
#include "exceptions/FileNotFoundException.h"
#include "exceptions/DirectoryNotFoundException.h"
#include "MarkovGenerator.h"
#include "helpers.h"
#include "consts.h"
#include "FileStorage.h"
#include "parse_file.h"
#include "exceptions/FileHasLessWordsException.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <cwctype>


void printUsageExamples() {
    std::wstring defaultUrlListFileName = str2wstr(DEFAULT_URL_LIST_FILE_NAME);
    std::wstring defaultDirectoryNameToStoreDownloadedFiles = str2wstr(DEFAULT_DIRECTORY_NAME_TO_STORE_DOWNLOADED_FILES);
    std::wstring defaultMarkovGeneratorStateFileName = str2wstr(DEFAULT_MARKOV_GENERATOR_STATE_FILE_NAME);
    std::size_t textLength = 10;
    std::wstring startingPhrase = L"starting phrase";

    std::wcout << std::endl;
    std::wcout << L"Examples:" << std::endl;
    std::wcout << L"1) To download and save text files using a url list file:"
               << std::endl;
    std::wcout << L"  - Using urls files \"" << defaultUrlListFileName << L"\""
               << L" and saving to directory \"" << defaultDirectoryNameToStoreDownloadedFiles << L"\""
               << std::endl;
    std::wcout << L"     markov -u " << defaultUrlListFileName
               << L" -d " << defaultDirectoryNameToStoreDownloadedFiles
               << L" download"
               << std::endl
               << std::endl;
    std::wcout << L"  - Using urls \"" << defaultUrlListFileName << L"\""
               << L" and saving to directory \"" << defaultDirectoryNameToStoreDownloadedFiles << L"\""
               << L" with deletion of previously downloaded files"
               << std::endl;
    std::wcout << L"     markov -u " << defaultUrlListFileName
               << L" -d " << defaultDirectoryNameToStoreDownloadedFiles
               << L" -c download"
               << std::endl
               << std::endl;

    std::wcout << L"2) To train Markov text generator on downloaded text files:"
               << std::endl;
    std::wcout << L"  - With the order " << DEFAULT_MARKOV_GENERATOR_ORDER << L" of Markov chain"
               << L" on all files from directory \"" << defaultDirectoryNameToStoreDownloadedFiles << L"\""
               << L" and saving its state to file \"" << defaultMarkovGeneratorStateFileName << L"\""
               << std::endl;
    std::wcout << L"     markov -d " << defaultDirectoryNameToStoreDownloadedFiles
               << L" -o " << DEFAULT_MARKOV_GENERATOR_ORDER
               << L" -f " << defaultMarkovGeneratorStateFileName
               << L" train"
               << std::endl
               << std::endl;

    std::wcout << L"3) To generate text using previously trained Markov text generator:"
               << std::endl;
    std::wcout << L"  - Generate text of length " << textLength
               << L" using starting phrase \"" << startingPhrase << L"\""
               << L" and state of Markov text generator loaded from file \"" << defaultMarkovGeneratorStateFileName << L"\""
               << std::endl;
    std::wcout << L"     markov -f " << defaultMarkovGeneratorStateFileName
               << L" -t \"" << startingPhrase << "\""
               << L" -l " << textLength
               << L" generate"
               << std::endl
               << std::endl;

    std::wcout << L"4) To combine file downloading and Markov generator training:"
               << std::endl;
    std::wcout << L"  - Download and train "
               << std::endl;
    std::wcout << L"     markov -u " << defaultUrlListFileName
               << L" -d " << defaultDirectoryNameToStoreDownloadedFiles
               << L" -o " << DEFAULT_MARKOV_GENERATOR_ORDER
               << L" -f " << defaultMarkovGeneratorStateFileName
               << L" dtrain"
               << std::endl
               << std::endl;

    std::wcout << L"5) To delete state file of Markov generator:"
               << std::endl;
    std::wcout << L"  - Delete state file "
               << std::endl;
    std::wcout << L"     markov -f " << defaultMarkovGeneratorStateFileName
               << L" delete"
               << std::endl;
}

bool checkAndPrintProvidedOptionForIgnorance(const cxxopts::ParseResult& parseResult, const std::string& optionPair) {
    std::size_t commaPosition = optionPair.find_first_of(',');
    if (commaPosition == std::string::npos) {
        throw std::logic_error(std::string(u8"Error! Invalid option \"") + optionPair + u8"\"!");
    }
    std::string optionShortName = optionPair.substr(0, commaPosition);
    std::string optionLongName = optionPair.substr(commaPosition + 1);
    if (parseResult.count(optionLongName)) {
        std::wcout << L"Warning! Provided option \"-" << str2wstr(optionShortName) << L",--" << str2wstr(optionLongName)
                   << L"\" is ignored!" << std::endl;
        return true;
    }
    return false;
}

void checkAndPrintProvidedOptionsVectorForIgnorance(const cxxopts::ParseResult& parseResult,
        const std::vector<std::string>& optionPairs) {
    bool anyIgnored = false;
    for (const auto& optionPair : optionPairs) {
        anyIgnored |= checkAndPrintProvidedOptionForIgnorance(parseResult, optionPair);
    }

    if (anyIgnored)
        std::wcout << std::endl;
}

void printOptionValuesForDownloadAllFilesCommand(const std::string& directoryNameToStoreDownloadedFiles,
        const std::string& urlListFileName, bool deleteAllStoredFiles) {
    std::wcout << L"  Directory for saving downloaded text files : " << std::endl
               << L"    " << str2wstr(std::filesystem::absolute(directoryNameToStoreDownloadedFiles)) << std::endl
               << L"  File with URL list : " << std::endl
               << L"    " << str2wstr(std::filesystem::absolute(urlListFileName)) << std::endl
               << L"  Delete all previously donwloaded files : " << boolToStr(deleteAllStoredFiles) << std::endl
               << std::endl;
}

void printOptionValuesForTrainMarkovGeneratorCommand(const std::string& directoryNameToStoreDownloadedFiles,
        std::size_t markovGeneratorOrder, const std::string& markovGeneratorStateFileName, bool useIncrementalTraining) {
    std::wcout << L"  Directory with saved training files : " << std::endl
               << L"    " << str2wstr(std::filesystem::absolute(directoryNameToStoreDownloadedFiles)) << std::endl
               << L"  Order of Markov chain : " << markovGeneratorOrder << std::endl
               << L"  File for saving state of trained Markov text generator : " << std::endl
               << L"    " << str2wstr(std::filesystem::absolute(markovGeneratorStateFileName)) << std::endl
               << L"  Use incremental training : " << boolToStr(useIncrementalTraining) << std::endl
               << std::endl;
}

void printOptionValuesForDownloadAllFilesAndTrainMarkovGeneratorCommand(const std::string& directoryNameToStoreDownloadedFiles,
        const std::string& urlListFileName, bool deleteAllStoredFiles, std::size_t markovGeneratorOrder,
        const std::string& markovGeneratorStateFileName, bool useIncrementalTraining) {
    std::wcout << L"  Directory for saving downloaded text files : " << std::endl
               << L"    " << str2wstr(std::filesystem::absolute(directoryNameToStoreDownloadedFiles)) << std::endl
               << L"  File with URL list : " << std::endl
               << L"    " << str2wstr(std::filesystem::absolute(urlListFileName)) << std::endl
               << L"  Delete all previously donwloaded files : " << boolToStr(deleteAllStoredFiles) << std::endl
               << L"  Order of Markov chain : " << markovGeneratorOrder << std::endl
               << L"  File for saving state of trained Markov text generator : " << std::endl
               << L"    " << str2wstr(std::filesystem::absolute(markovGeneratorStateFileName)) << std::endl
               << L"  Use incremental training : " << boolToStr(useIncrementalTraining) << std::endl
               << std::endl;
}

void downloadAllFiles(const std::string& directoryNameToStoreDownloadedFiles, const std::string& urlListFileName,
        bool deleteAllStoredFiles) {
    FileStorage storage(directoryNameToStoreDownloadedFiles, urlListFileName);
    if (deleteAllStoredFiles) {
        std::wcout << L"Deleting all previously downloaded files... ";
        storage.deleteAllFiles();
        std::wcout << L"Done" << std::endl;
    }
    std::wcout << L"Downloading files..." << std::endl;
    std::size_t downloadedFilesCount = storage.downloadAllFiles();
    std::wcout << L"Done" << std::endl;
    std::wcout << downloadedFilesCount << L" file(s) downloaded" << std::endl;
}

void trainMarkovGeneratorOnAllFiles(const std::string& directoryNameToStoreDownloadedFiles,
        std::size_t markovGeneratorOrder, const std::string& markovGeneratorStateFileName, bool useIncrementalTraining) {
    if (!std::filesystem::exists(directoryNameToStoreDownloadedFiles)) {
        throw DirectoryNotFoundException(std::string(u8"Error! Directory \'")
                                         + directoryNameToStoreDownloadedFiles + u8"\' was not found!");
    }

    FileStorage storage(directoryNameToStoreDownloadedFiles);
    if (!storage.hasAnyNoneEmptyFile()) {
        std::wcout << L"No none-empty files for training!" << std::endl;
        return;
    }

    MarkovGenerator generator(markovGeneratorOrder);
    if (useIncrementalTraining) {
        std::wcout << L"Trying to load previous state of markov generator from file \""
                   << str2wstr(markovGeneratorStateFileName) <<  "\"... ";
        if (std::filesystem::exists(markovGeneratorStateFileName)) {
            generator = MarkovGenerator::deserialize(markovGeneratorStateFileName);
            generator.switchToTrainingMode();
            std::wcout << L"Done" << std::endl;
        } else {
            std::wcout << L"File does not exist. Training from scratch!" << std::endl;
        }
    }

    std::string fileNameStr;
    std::wstring fullFileName;
    std::size_t processedFilesCount = 0;

    std::wcout << L"Training markov generator... " << std::endl;
    for (auto& fileName : storage.getAllFileNames()) {
        try {
            fileNameStr = wstr2str(fileName);
            fullFileName = std::filesystem::absolute(fileNameStr).wstring();
            std::wcout << L"  " << fullFileName << L" ";
            generator.train(parseFile(fileNameStr));
            ++processedFilesCount;
            std::wcout << L"Done" << std::endl;
        }
        catch (const FileHasLessWordsException &e) {
            std::wcout << L"Skipped (" << e.what() << ")" << std::endl;
        }
        catch (const FileNotFoundException &e) {
            std::wcout << L"Skipped (not found)" << std::endl;
        }
    }
    std::wcout << L"Done" << std::endl;
    std::wcout << processedFilesCount << L" file(s) processed" << std::endl;

    generator.switchToGenerationMode();
    std::wcout << L"Saving markov generator state to file \"" << str2wstr(markovGeneratorStateFileName) << L"\"... ";
    generator.serialize(markovGeneratorStateFileName);
    std::wcout << L"Done" << std::endl;

    //std::wcout << generator.generateText({L"журнал", L"пособий"}, 3) << std::endl;
}
void downloadAllFilesAndTrainMarkovGenerator(const std::string& directoryNameToStoreDownloadedFiles,
        const std::string& urlListFileName, bool deleteAllStoredFiles, std::size_t markovGeneratorOrder,
        const std::string& markovGeneratorStateFileName, bool useIncrementalTraining) {
    downloadAllFiles(directoryNameToStoreDownloadedFiles, urlListFileName, deleteAllStoredFiles);
    trainMarkovGeneratorOnAllFiles(directoryNameToStoreDownloadedFiles, markovGeneratorOrder,
        markovGeneratorStateFileName, useIncrementalTraining);
}

void generateTextUsingMarkovGenerator(const std::string& markovGeneratorStateFileName, std::size_t generatedTextLength,
        const std::string& startingPhrase) {
    std::wcout << L"  File for loading state of trained Markov generator : " << std::endl
               << L"    " << str2wstr(std::filesystem::absolute(markovGeneratorStateFileName)) << std::endl
               << L"  Length of text to generate: " << generatedTextLength << std::endl;
    std::wcout << L"Loading trained state of markov text generator... ";
    MarkovGenerator generator = MarkovGenerator::deserialize(markovGeneratorStateFileName);
    std::wcout << L"Done" << std::endl;
    std::size_t order = generator.getOrder();
    std::wcout << L"  Order of Markov chain : " << order << std::endl;

    std::vector<std::wstring> words;
    if (!startingPhrase.empty()) {
        std::wcout << L"  Starting phrase : \"" << str2wstr(startingPhrase) << L"\"" << std::endl;
        stringToWordsVector(str2wstr(startingPhrase), words);
    } else {
        std::wstring inputStartingPhrase;
        std::wcout << L"Please, input starting phrase (" << order << L" word(s)):" << std::endl;
        std::getline(std::wcin, inputStartingPhrase);
        stringToWordsVector(inputStartingPhrase, words);
    }
    std::wcout << L"  Starting phrase after pre-processing : \"" << joinStrings(words) << "\"" << std::endl;
    std::wcout << std::endl;
    if (words.size() != order) {
        std::wcout << L"Error! Starting phrase has " << words.size() << L" word(s), but it should contain "
                   << order << L"!" << std::endl;
    } else {
        std::wcout << L"Generated text:" << std::endl;
        std::wcout << generator.generateText(words, generatedTextLength) << std::endl;
    }
}

void deleteStateOfMarkovGenerator(const std::string& markovGeneratorStateFileName) {
    try {
        std::wcout << L"Deletion of state file " << std::filesystem::absolute(markovGeneratorStateFileName) << "... ";
        std::filesystem::remove(markovGeneratorStateFileName);
        std::wcout << L"Done" << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::wcout << std::endl;
        std::wcout << L"Warning! " << e.what() << std::endl;
    }
}

void parseAndProcessCommand(int argc, char* argv[]) {
    try {
        cxxopts::Options options(u8"markov", u8"Markov text generator of n-th order");
        options.positional_help(u8"[command]")
                .show_positional_help();

        std::string directoryNameToStoreDownloadedFiles;
        std::string urlListFileName;
        bool deleteAllStoredFiles;
        std::size_t markovGeneratorOrder;
        std::string markovGeneratorStateFileName;
        bool useIncrementalTraining;
        std::size_t generatedTextLength;
        std::string startingPhrase;

        options.add_options()
                (COMMAND_OPTION_LONG, u8"Command to execute (download, train, dtrain, generate, delete)",
                        cxxopts::value<std::string>())
                (HELP_OPTION_PAIR, u8"Print help")
                (STORAGE_DIRECTORY_OPTION_PAIR, u8"Directory to save downloaded files for training",
                 cxxopts::value<std::string>(directoryNameToStoreDownloadedFiles)
                         ->default_value(DEFAULT_DIRECTORY_NAME_TO_STORE_DOWNLOADED_FILES))
                (URL_LIST_FILE_OPTION_PAIR, u8"File with urls of training files",
                 cxxopts::value<std::string>(urlListFileName)
                         ->default_value(DEFAULT_URL_LIST_FILE_NAME))
                (CLEAR_DIRECTORY_OPTION_PAIR, u8"Delete all previously downloaded training files in directory",
                 cxxopts::value<bool>(deleteAllStoredFiles)
                         ->default_value(std::to_string(DEFAULT_DELETE_ALL_STORED_FILES)))
                (MARKOV_GENERATOR_ORDER_OPTION_PAIR, u8"Order of Markov generator",
                 cxxopts::value<std::size_t>(markovGeneratorOrder)
                         ->default_value(std::to_string(DEFAULT_MARKOV_GENERATOR_ORDER)))
                (MARKOV_GENERATOR_STATE_FILE_OPTION_PAIR, u8"Markov generator state file name",
                 cxxopts::value<std::string>(markovGeneratorStateFileName)
                         ->default_value(DEFAULT_MARKOV_GENERATOR_STATE_FILE_NAME))
                (INCREMENTAL_TRAINING_OPTION_PAIR, u8"Use incremental training",
                 cxxopts::value<bool>(useIncrementalTraining)
                         ->default_value(std::to_string(DEFAULT_USE_INCREMENTAL_TRAINING)))
                (GENERATED_TEXT_LENGTH_OPTION_PAIR, u8"Generated text length (words count)",
                 cxxopts::value<std::size_t>(generatedTextLength)
                         ->default_value(std::to_string(DEFAULT_GENERATED_TEXT_SIZE)))
                (STARTING_PHRASE_OPTION_PAIR, u8"Starting phrase",
                 cxxopts::value<std::string>(startingPhrase)
                         ->default_value(""));

        options.parse_positional(COMMAND_OPTION_LONG);

        auto result = options.parse(argc, argv);

        directoryNameToStoreDownloadedFiles = trim(directoryNameToStoreDownloadedFiles);
        urlListFileName = trim(urlListFileName);
        markovGeneratorStateFileName = trim(markovGeneratorStateFileName);

        if (directoryNameToStoreDownloadedFiles.empty()) {
            throw std::logic_error(std::string(std::string(u8"Error! Directory name to store downloaded files for trainig (")
                + STORAGE_DIRECTORY_OPTION_PAIR + ") cannot be empty!"));
        }
        if (urlListFileName.empty()) {
            throw std::logic_error(std::string(std::string(u8"Error! File with urls of training files (")
                + URL_LIST_FILE_OPTION_PAIR + ") cannot be empty!"));
        }
        if (markovGeneratorStateFileName.empty()) {
            throw std::logic_error(std::string(std::string(u8"Error! Markov generator state file name (")
                + MARKOV_GENERATOR_STATE_FILE_OPTION_PAIR + ") cannot be empty!"));
        }

        if (markovGeneratorOrder == 0) {
            throw std::logic_error(std::string(u8"Error! Invalid value ") + std::to_string(markovGeneratorOrder)
                + u8" of option -n,--order!");
        }

        if (result.count(HELP_OPTION_LONG)) {
            std::wcout << str2wstr(options.help({}));
            printUsageExamples();
        }

        try {
            if (result.count(COMMAND_OPTION_LONG)) {
                std::wstring command = str2wstr(result[COMMAND_OPTION_LONG].as<std::string>());
                if (command == L"download") {
                    checkAndPrintProvidedOptionsVectorForIgnorance(result, {MARKOV_GENERATOR_ORDER_OPTION_PAIR,
                        MARKOV_GENERATOR_STATE_FILE_OPTION_PAIR, GENERATED_TEXT_LENGTH_OPTION_PAIR,
                        STARTING_PHRASE_OPTION_PAIR, INCREMENTAL_TRAINING_OPTION_PAIR});

                    std::wcout << L"Downloading command is selected" << std::endl;
                    printOptionValuesForDownloadAllFilesCommand(directoryNameToStoreDownloadedFiles, urlListFileName,
                        deleteAllStoredFiles);
                    downloadAllFiles(directoryNameToStoreDownloadedFiles, urlListFileName, deleteAllStoredFiles);
                } else if (command == L"train") {
                    checkAndPrintProvidedOptionsVectorForIgnorance(result, {URL_LIST_FILE_OPTION_PAIR,
                        CLEAR_DIRECTORY_OPTION_PAIR, GENERATED_TEXT_LENGTH_OPTION_PAIR, STARTING_PHRASE_OPTION_PAIR});

                    std::wcout << L"Training command is selected" << std::endl;
                    printOptionValuesForTrainMarkovGeneratorCommand(directoryNameToStoreDownloadedFiles,
                        markovGeneratorOrder, markovGeneratorStateFileName, useIncrementalTraining);
                    trainMarkovGeneratorOnAllFiles(directoryNameToStoreDownloadedFiles, markovGeneratorOrder,
                        markovGeneratorStateFileName, useIncrementalTraining);
                } else if (command == L"dtrain") {
                    checkAndPrintProvidedOptionsVectorForIgnorance(result, {GENERATED_TEXT_LENGTH_OPTION_PAIR,
                        STARTING_PHRASE_OPTION_PAIR});

                    std::wcout << L"Dtrain (downloading and train) command is selected" << std::endl;
                    printOptionValuesForDownloadAllFilesAndTrainMarkovGeneratorCommand(directoryNameToStoreDownloadedFiles,
                        urlListFileName, deleteAllStoredFiles, markovGeneratorOrder, markovGeneratorStateFileName,
                        useIncrementalTraining);
                    downloadAllFilesAndTrainMarkovGenerator(directoryNameToStoreDownloadedFiles,
                        urlListFileName, deleteAllStoredFiles, markovGeneratorOrder, markovGeneratorStateFileName,
                        useIncrementalTraining);

                } else if (command == L"generate") {
                    checkAndPrintProvidedOptionsVectorForIgnorance(result, {STORAGE_DIRECTORY_OPTION_PAIR,
                        URL_LIST_FILE_OPTION_PAIR, CLEAR_DIRECTORY_OPTION_PAIR, MARKOV_GENERATOR_ORDER_OPTION_PAIR,
                        INCREMENTAL_TRAINING_OPTION_PAIR});

                    std::wcout << L"Generate text command is selected" << std::endl;
                    generateTextUsingMarkovGenerator(markovGeneratorStateFileName, generatedTextLength, startingPhrase);
                } else if (command == L"delete") {
                    checkAndPrintProvidedOptionsVectorForIgnorance(result, {STORAGE_DIRECTORY_OPTION_PAIR,
                        URL_LIST_FILE_OPTION_PAIR, CLEAR_DIRECTORY_OPTION_PAIR, MARKOV_GENERATOR_ORDER_OPTION_PAIR,
                        INCREMENTAL_TRAINING_OPTION_PAIR, GENERATED_TEXT_LENGTH_OPTION_PAIR,
                        STARTING_PHRASE_OPTION_PAIR});

                    std::wcout << L"Deletion of Markov generator state file is selected" << std::endl;
                    deleteStateOfMarkovGenerator(markovGeneratorStateFileName);
                } else {
                    std::wcout << L"Error! Unknown command \"" << command << "\"!" << std::endl;
                    std::wcout << L"Error! Please provide one of the following commands:" << std::endl
                               << L"  download \tTo download and save text files using a url list file" << std::endl
                               << L"  train \tTo train Markov text generator on downloaded text files" << std::endl
                               << L"  dtrain \tTo generate text using previously trained Markov text generator" << std::endl
                               << L"  generate \tTo combine file downloading and Markov generator training" << std::endl
                               << L"  delete \tTo delete state file of Markov generator" << std::endl
                               << std::endl;

                }
            } else {
                printUsageExamples();
                std::wcout << str2wstr(options.help({}));
            }
        } catch (const std::exception& e) {
            std::wcout << e.what() << std::endl;
        }
    }
    catch (const cxxopts::OptionException& e)
    {
        std::wcout << u8"Error parsing options: " << e.what() << std::endl;
    }
}
//
// Created by datas on 4/28/2020.
//

#include "MarkovGenerator.h"
#include "helpers.h"
#include "exceptions/FileHasLessWordsException.h"
#include "exceptions/StartingTextHasLessWordsException.h"
#include "exceptions/FileNotFoundException.h"
#include <iostream>

void MarkovGenerator::train(const std::vector<std::wstring>& text) {
    if (isTrainingFinished) {
        switchToTrainingMode();
    }

    std::size_t textSize = text.size();
    if (textSize < order + 1)
        throw FileHasLessWordsException(std::string(u8"File has ") + std::to_string(textSize) +
                          u8" word(s) that is less than " + std::to_string(order + 1));

    std::list<std::wstring> currentWordsList(text.begin(), text.begin() + order);
    for (std::size_t i = order; i < textSize; ++i) {
        std::wstring keyString = joinStrings(currentWordsList);
        if (selectionMap.find(keyString) == selectionMap.end()) {
            selectionMap[keyString] = MarkovSelector();
        }
        selectionMap[keyString].update(text[i]);
        currentWordsList.pop_front();
        currentWordsList.push_back(text[i]);
    }
}

std::wstring MarkovGenerator::generateText(const std::vector<std::wstring> &startingTextWords, std::size_t length) {
    if (startingTextWords.size() != order) {
        throw StartingTextHasLessWordsException(std::string(u8"Starting text has ") +
                        std::to_string(startingTextWords.size()) + u8" word(s), which is less than chain size " +
                        std::to_string(order));
    }
    if (!isTrainingFinished) {
        switchToGenerationMode();
    }

    std::wstring keyString, nextWord;
    std::list<std::wstring> currentWordsList(startingTextWords.begin(), startingTextWords.end());

    std::wstring resultText = joinStrings(currentWordsList);
    keyString = resultText;
    for (std::size_t i = 0; i < length; ++i) {
        if (selectionMap.find(keyString) == selectionMap.end())
            break;
        nextWord = selectionMap[keyString].selectRandomWord();
        resultText += L" " + nextWord;
        currentWordsList.pop_front();
        currentWordsList.push_back(nextWord);
        keyString = joinStrings(currentWordsList);
    }
    return resultText;
}

void MarkovGenerator::serialize(const std::string& fileName) const {
    try {
        std::ofstream out(fileName, std::ios::binary);
        if (!out.is_open()) {
            throw FileNotFoundException(std::string(u8"File \"") + fileName + u8"\" was not found!");
        }
        out.write((char *)&order, sizeof order);
        std::size_t mapSize = selectionMap.size();
        out.write((char *)&mapSize, sizeof mapSize);
        out.write((char *)&isTrainingFinished, sizeof isTrainingFinished);

        std::size_t tmpStringSize;
        std::string tmpString;

        for (const auto &pair : selectionMap) {
            tmpString = wstr2str(pair.first);
            tmpStringSize = tmpString.size();
            out.write((char *)&tmpStringSize, sizeof tmpStringSize);
            out.write(tmpString.data(), tmpStringSize);
            pair.second.serialize(out);
        }
    } catch (const std::ofstream::failure& e) {
        throw;
    }
}

MarkovGenerator MarkovGenerator::deserialize(const std::string& fileName) {
    try {
        std::ifstream inp(fileName, std::ios::binary);
        if (!inp.is_open()) {
            throw FileNotFoundException(std::string(u8"File \"") + fileName + u8"\" was not found!");
        }

        std::size_t order;
        std::size_t keysCount;
        std::wstring keyString;
        bool isTrainingFinished;
        std::size_t tmpStringSize;
        char* tmpString;

        inp.read((char *)&order, sizeof order);
        inp.read((char *)&keysCount, sizeof keysCount);
        inp.read((char *)&isTrainingFinished, sizeof isTrainingFinished);

        MarkovGenerator generator(order);
        generator.isTrainingFinished = isTrainingFinished;
        generator.selectionMap.reserve(keysCount);

        for (std::size_t i = 0; i < keysCount; ++i) {
            inp.read((char *)&tmpStringSize, sizeof tmpStringSize);
            tmpString = new char [tmpStringSize + 1];
            inp.read(tmpString, tmpStringSize);
            tmpString[tmpStringSize] = '\0';
            keyString = str2wstr(tmpString);
            delete[] tmpString;

            generator.selectionMap[keyString] = MarkovSelector();
            generator.selectionMap[keyString].deserialize(inp, isTrainingFinished);
        }
        return generator;
    } catch (const std::ifstream::failure& e) {
        throw;
    }
}

void MarkovGenerator::switchToGenerationMode() {
    for (auto& pair : selectionMap) {
        pair.second.switchToInferenceMode();
    }
    isTrainingFinished = true;
}

void MarkovGenerator::switchToTrainingMode() {
    for (auto& pair : selectionMap) {
        pair.second.switchToTrainingMode();
    }
    isTrainingFinished = false;
}



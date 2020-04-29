//
// Created by datas on 4/28/2020.
//

#include "MarkovGenerator.h"
#include "helpers.h"
#include "exceptions/FileHasLessWordsException.h"
#include "exceptions/StartingTextHasLessWordsException.h"

void MarkovGenerator::train(const std::vector<std::string>& text) {
    if (isTrainingFinished) {
        switchToTrainingMode();
    }

    std::size_t textSize = text.size();
    if (textSize < chainSize)
        throw FileHasLessWordsException(std::string("File has ") + std::to_string(textSize) +
                          " word(s) that is less than " + std::to_string(chainSize));

    std::list<std::string> currentWordsList(text.begin(), text.begin() + chainSize);
    for (std::size_t i = chainSize; i < textSize; ++i) {
        std::string keyString = joinStrings(currentWordsList);
        if (selectionMap.find(keyString) == selectionMap.end()) {
            selectionMap[keyString] = MarkovSelector();
        }
        selectionMap[keyString].update(text[i]);
        currentWordsList.pop_front();
        currentWordsList.push_back(text[i]);
    }
}

std::string MarkovGenerator::generateText(const std::vector<std::string> &startingTextWords, std::size_t length) {
    if (startingTextWords.size() != chainSize) {
        throw StartingTextHasLessWordsException(std::string("Starting text has ") +
                        std::to_string(startingTextWords.size()) + " word(s), which is less than chain size " +
                        std::to_string(chainSize));
    }
    if (!isTrainingFinished) {
        switchToInferenceMode();
    }

    std::string keyString, nextWord;
    std::list<std::string> currentWordsList(startingTextWords.begin(), startingTextWords.end());

    std::string resultText = joinStrings(currentWordsList);
    keyString = resultText;
    for (std::size_t i = 0; i < length; ++i) {
        if (selectionMap.find(keyString) == selectionMap.end())
            break;
        nextWord = selectionMap[keyString].selectRandomWord();
        resultText += " " + nextWord;
        currentWordsList.pop_front();
        currentWordsList.push_back(nextWord);
        keyString = joinStrings(currentWordsList);
    }
    return resultText;
}

void MarkovGenerator::serialize(std::ofstream& out) const {
    out << selectionMap.size() << isTrainingFinished;
    for (const auto& pair : selectionMap) {
        out << pair.first;
        pair.second.serialize(out);
    }
}

void MarkovGenerator::deserialize(std::ifstream& inp) {
    std::size_t keysCount;
    std::string keySentence;

    inp >> keysCount >> isTrainingFinished;

    selectionMap.clear();
    selectionMap.reserve(keysCount);
    for (std::size_t i = 0; i < keysCount; ++i) {
        std::getline(inp, keySentence);
        selectionMap[keySentence] = MarkovSelector();
        selectionMap[keySentence].deserialize(inp, isTrainingFinished);
    }
}

void MarkovGenerator::switchToInferenceMode() {
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



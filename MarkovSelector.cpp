//
// Created by datas on 4/28/2020.
//

#include <algorithm>
#include <chrono>
#include "MarkovSelector.h"
#include "helpers.h"

void MarkovSelector::update(const std::wstring& word) {
    ++wordFrequency[word];
    ++wordsCount;
}

std::wstring MarkovSelector::selectRandomWord() {
    if (!isTrainingFinished) {
        switchToInferenceMode();
    }
    int randomValue = getRandomSizeTNumber(1, wordsCount );
    auto lowerBoundIt = std::lower_bound(cumulativeFrequencyPair.begin(), cumulativeFrequencyPair.end(), randomValue,
        [](const std::pair<std::size_t, std::wstring>& pair, std::size_t value) {
            return pair.first < value;
        }
    );
    return lowerBoundIt->second;
}

void MarkovSelector::serialize(std::ofstream& out) const {
    std::size_t size;
    std::size_t tmpStringSize;
    std::string tmpString;
    if (isTrainingFinished) {
        size = cumulativeFrequencyPair.size();
        out.write((char *)&size, sizeof size);
        out.write((char *)&wordsCount, sizeof wordsCount);
        for (const auto& pair : cumulativeFrequencyPair) {
            out.write((char *)&pair.first, sizeof pair.first);
            tmpString = wstr2str(pair.second);
            tmpStringSize = tmpString.size();
            out.write((char *)&tmpStringSize, sizeof tmpStringSize);
            out.write(tmpString.data(), tmpStringSize);
        }
    } else {
        size = wordFrequency.size();
        out.write((char *)&size, sizeof size);
        out.write((char *)&wordsCount, sizeof wordsCount);
        for (const auto& pair : wordFrequency) {
            tmpString = wstr2str(pair.first);
            tmpStringSize = tmpString.size();
            out.write((char *)&tmpStringSize, sizeof tmpStringSize);
            out.write(tmpString.data(), tmpStringSize);
            out.write((char *)&pair.second, sizeof pair.second);
        }
    }
}

void MarkovSelector::deserialize(std::ifstream& inp, bool isTrainingFinished) {
    std::size_t frequency;

    this->isTrainingFinished = isTrainingFinished;
    wordFrequency.clear();
    cumulativeFrequencyPair.clear();

    std::size_t keysCount;
    inp.read((char *)&keysCount, sizeof keysCount);
    inp.read((char *)&wordsCount, sizeof wordsCount);
    std::size_t tmpStringSize;
    char* tmpString;

    if (isTrainingFinished) {
        cumulativeFrequencyPair.reserve(keysCount);
        for (std::size_t i = 0; i < keysCount; ++i) {
            inp.read((char *)&frequency, sizeof frequency);
            inp.read((char *)&tmpStringSize, sizeof tmpStringSize);
            tmpString = new char [tmpStringSize + 1];
            inp.read(tmpString, tmpStringSize);
            tmpString[tmpStringSize] = '\0';
            cumulativeFrequencyPair.emplace_back(frequency, str2wstr(std::string(tmpString)));
            delete[] tmpString;
        }
    } else {
        wordFrequency.reserve(keysCount);
        for (std::size_t i = 0; i < keysCount; ++i) {
            inp.read((char *)&tmpStringSize, sizeof tmpStringSize);
            tmpString = new char [tmpStringSize + 1];
            inp.read(tmpString, tmpStringSize);
            tmpString[tmpStringSize] = '\0';
            inp.read((char *)&frequency, sizeof frequency);
            wordFrequency[str2wstr(std::string(tmpString))] = frequency;
            delete[] tmpString;
        }
    }
}

void MarkovSelector::switchToInferenceMode() {
    if (isTrainingFinished)
        return;

    std::size_t keysCount = wordFrequency.size();
    cumulativeFrequencyPair.resize(keysCount);
    auto it = wordFrequency.cbegin();
    if (keysCount > 0) {
        cumulativeFrequencyPair[0] = make_pair(it->second, it->first);
        ++it;
    }
    for (int i = 1; i < keysCount; ++i, ++it) {
        cumulativeFrequencyPair[i] = make_pair(cumulativeFrequencyPair[i - 1].first + it->second, it->first);
    }
    wordFrequency.clear();
    isTrainingFinished = true;
}

void MarkovSelector::switchToTrainingMode() {
    if (!isTrainingFinished)
        return;

    std::size_t keysCount = cumulativeFrequencyPair.size();
    wordFrequency.reserve(keysCount);
    std::size_t previousFrequency = 0;
    for (const auto& pair : cumulativeFrequencyPair) {
        wordFrequency[pair.second] = pair.first - previousFrequency;
        previousFrequency = pair.first;
    }

    cumulativeFrequencyPair.clear();
    isTrainingFinished = false;
}



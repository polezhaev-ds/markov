//
// Created by datas on 4/28/2020.
//

#include <algorithm>
#include <chrono>
#include "MarkovSelector.h"
#include "helpers.h"

//std::mt19937 MarkovSelector::generator; // (std::chrono::system_clock::now().time_since_epoch().count());
//std::uniform_int_distribution<std::size_t> MarkovSelector::uniformDistribution;

void MarkovSelector::update(const std::string& word) {
    ++wordFrequency[word];
    ++wordsCount;
}

std::string MarkovSelector::selectRandomWord() {
    if (!isTrainingFinished) {
        switchToInferenceMode();
    }
    int randomValue = getRandomSizeTNumber(1, wordsCount );
    auto lowerBoundIt = std::lower_bound(cumulativeFrequencyPair.begin(), cumulativeFrequencyPair.end(), randomValue,
        [](const std::pair<std::size_t, std::string>& pair, std::size_t value) {
            return pair.first < value;
        }
    );
    return lowerBoundIt->second;
}

void MarkovSelector::serialize(std::ofstream& out) const {
    if (isTrainingFinished) {
        out << cumulativeFrequencyPair.size() << wordsCount;
        for (const auto& pair : cumulativeFrequencyPair) {
            out << pair.first << pair.second;
        }
    } else {
        out << wordFrequency.size() << wordsCount;
        for (const auto& pair : wordFrequency) {
            out << pair.first << pair.second;
        }
    }
}

void MarkovSelector::deserialize(std::ifstream& inp, bool isTrainingFinished) {
    std::string word;
    std::size_t frequency;

    this->isTrainingFinished = isTrainingFinished;
    wordFrequency.clear();
    cumulativeFrequencyPair.clear();

    std::size_t keysCount;
    inp >> keysCount >> wordsCount;

    if (isTrainingFinished) {
        cumulativeFrequencyPair.reserve(keysCount);
        for (std::size_t i = 0; i < keysCount; ++i) {
            inp >> frequency >> word;
            cumulativeFrequencyPair.emplace_back(frequency, word);
        }
    } else {
        wordFrequency.reserve(keysCount);
        for (std::size_t i = 0; i < keysCount; ++i) {
            inp >> word >> frequency;
            wordFrequency[word] = frequency;
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



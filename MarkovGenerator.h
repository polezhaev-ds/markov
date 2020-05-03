//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_MARKOVGENERATOR_H
#define MARKOV_MARKOVGENERATOR_H

#include "MarkovSelector.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>

class MarkovGenerator {
public:
    explicit MarkovGenerator(std::size_t order):
        order(order), isTrainingFinished(false)
    {
        if (order == 0)
            throw std::invalid_argument(u8"Error! Invalid argument order! It should be greater than zero!");
    }

    MarkovGenerator(const MarkovGenerator& generator) = default;
    MarkovGenerator(MarkovGenerator&& generator) = default;
    MarkovGenerator& operator = (const MarkovGenerator& generator) = default;
    MarkovGenerator& operator = (MarkovGenerator&& generator) = default;

    void train(const std::vector<std::wstring>& text);
    std::wstring generateText(const std::vector<std::wstring>& startingTextWords, std::size_t length);

    void serialize(const std::string& fileName) const;
    static MarkovGenerator deserialize(const std::string& fileName);

    void switchToGenerationMode();
    void switchToTrainingMode();

    [[nodiscard]] std::size_t getOrder() const {
        return order;
    }
private:
    std::size_t order;
    bool isTrainingFinished;
    std::unordered_map<std::wstring, MarkovSelector> selectionMap;

};


#endif //MARKOV_MARKOVGENERATOR_H

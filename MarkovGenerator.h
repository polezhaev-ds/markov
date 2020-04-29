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
    MarkovGenerator(std::size_t chainSize):
        chainSize(chainSize), isTrainingFinished(false)
    {
    }

    void train(const std::vector<std::string>& text);
    std::string generateText(const std::vector<std::string>& startingTextWords, std::size_t length);

    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& inp);

    void switchToInferenceMode();
    void switchToTrainingMode();
private:
    std::size_t chainSize;
    bool isTrainingFinished;
    std::unordered_map<std::string, MarkovSelector> selectionMap;

};


#endif //MARKOV_MARKOVGENERATOR_H

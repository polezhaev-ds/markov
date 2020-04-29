//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_MARKOVSELECTOR_H
#define MARKOV_MARKOVSELECTOR_H

#include <unordered_map>
#include <string>
#include <vector>
#include <random>
#include <fstream>

class MarkovSelector {
public:
    MarkovSelector():
        wordsCount(0), isTrainingFinished(false)
    {
    }

    void update(const std::string& word);

    std::string selectRandomWord();

    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& inp, bool isTrainingFinished);

    void switchToInferenceMode();
    void switchToTrainingMode();

private:

    std::unordered_map<std::string, std::size_t> wordFrequency;
    std::vector<std::pair<std::size_t, std::string>> cumulativeFrequencyPair;
    std::size_t wordsCount;
    bool isTrainingFinished;
};


#endif //MARKOV_MARKOVSELECTOR_H

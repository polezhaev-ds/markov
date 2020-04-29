//
// Created by datas on 4/28/2020.
//

#include "helpers.h"
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

std::random_device randomDevice;
std::mt19937 randomGenerator(std::chrono::system_clock::now().time_since_epoch().count());

std::string joinStrings(const std::list<std::string>& strings) {
    std::stringstream stringStream;
    for (auto it = strings.begin(); it != strings.end(); ++it) {
        if (it != strings.begin())
            stringStream << " ";
        stringStream << *it;
    }
    return stringStream.str();
}

void toLower(std::string& string) {
    std::transform(string.begin(), string.end(), string.begin(),
        [](auto ch) {
            return std::tolower(ch);
        }
    );
}

std::size_t getRandomSizeTNumber(std::size_t from, std::size_t to) {
    std::uniform_int_distribution<std::size_t> distribution(from, to);
    return distribution(randomGenerator);
}
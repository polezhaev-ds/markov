//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_HELPERS_H
#define MARKOV_HELPERS_H

#include <list>
#include <string>

std::string joinStrings(const std::list<std::string>& strings);

void toLower(std::string& string);

std::size_t getRandomSizeTNumber(std::size_t from, std::size_t to);

#endif //MARKOV_HELPERS_H

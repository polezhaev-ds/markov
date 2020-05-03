//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_PARSE_FILE_H
#define MARKOV_PARSE_FILE_H

#include <vector>
#include <string>

std::vector<std::wstring> parseFile(const std::string& fileName);

void stringToWordsVector(const std::wstring& str, std::vector<std::wstring>& words);

#endif //MARKOV_PARSE_FILE_H

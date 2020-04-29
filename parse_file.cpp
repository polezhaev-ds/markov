//
// Created by datas on 4/28/2020.
//

#include "parse_file.h"
#include "helpers.h"
#include "exceptions/FileNotFoundException.h"
#include <fstream>
#include <cctype>


std::vector<std::string> parseFile(const std::string& fileName) {
    std::ifstream inp(fileName);
    if (!inp.is_open()) {
        throw FileNotFoundException(std::string("File '") + fileName + "' was not found!");
    }
    std::vector<std::string> textWords;
    std::string line;
    std::string currentWord;
    std::size_t lineSize;

    while (!inp.eof()) {
        std::getline(inp, line);

        toLower(line);
        lineSize = line.size();
        for (std::size_t i = 0; i < lineSize; ++i) {
            if ((std::ispunct(line[i]) || std::isspace(line[i])) && !currentWord.empty()) {
                textWords.push_back(currentWord);
                currentWord = "";
            } else if (!std::ispunct(line[i]) && !std::isspace(line[i])) {
                currentWord += line[i];
            }
        }
        if (!currentWord.empty()) {
            textWords.push_back(currentWord);
            currentWord = "";
        }
    }
    return textWords;
}

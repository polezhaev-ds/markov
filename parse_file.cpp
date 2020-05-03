//
// Created by datas on 4/28/2020.
//

#include "parse_file.h"
#include "helpers.h"
#include "exceptions/FileNotFoundException.h"
#include <fstream>
#include <cctype>

void stringToWordsVector(const std::wstring& str, std::vector<std::wstring>& words) {
    std::wstring line = str;
    toLower(line);
    std::size_t lineSize = line.size();
    std::wstring currentWord;

    for (std::size_t i = 0; i < lineSize; ++i) {
        if ((std::iswpunct(line[i]) || std::iswspace(line[i])) && !currentWord.empty()) {
            words.push_back(currentWord);
            currentWord = L"";
        } else if (!std::iswpunct(line[i]) && !std::iswspace(line[i])) {
            currentWord += line[i];
        }
    }
    if (!currentWord.empty()) {
        words.push_back(currentWord);
        currentWord = L"";
    }
}

std::vector<std::wstring> parseFile(const std::string& fileName) {
    std::ifstream inp(fileName);
    if (!inp.is_open()) {
        throw FileNotFoundException(std::string(u8"File '") + fileName + u8"' was not found!");
    }
    std::vector<std::wstring> textWords;
    std::string tempLine;

    while (!inp.eof()) {
        std::getline(inp, tempLine);
        stringToWordsVector(str2wstr(tempLine), textWords);
    }
    return textWords;
}

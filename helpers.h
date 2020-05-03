//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_HELPERS_H
#define MARKOV_HELPERS_H

#include <list>
#include <string>
#include <openssl/md5.h>
#include <iomanip>


void toLower(std::wstring& string);

std::size_t getRandomSizeTNumber(std::size_t from, std::size_t to);

std::wstring str2wstr(const std::string& str);
std::string wstr2str(const std::wstring& wstr);

std::string hexStr(unsigned char* data, int len);

std::string md5(const std::string& str);

std::wstring boolToStr(bool value);

template <typename TContainer>
std::wstring joinStrings(const TContainer& strings) {
    std::wstringstream stringStream;
    for (auto it = strings.begin(); it != strings.end(); ++it) {
        if (it != strings.begin())
            stringStream << L" ";
        stringStream << *it;
    }
    return stringStream.str();
}

template <typename TString>
TString& trimLeft(TString& str, TString& whitSpaceChars)
{
    str.erase(0, str.find_first_not_of(whitSpaceChars));
    return str;
}

template <typename TString>
TString& trimRight(TString& str, TString& whitSpaceChars)
{
    str.erase(str.find_last_not_of(whitSpaceChars) + 1);
    return str;
}

std::string& trim(std::string& str);
std::wstring& trim(std::wstring& str);

#endif //MARKOV_HELPERS_H

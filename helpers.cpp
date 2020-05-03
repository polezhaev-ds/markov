//
// Created by datas on 4/28/2020.
//

#include "helpers.h"
#include "consts.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <locale>
#include <codecvt>
#include <iostream>
#include <iomanip>


std::random_device randomDevice;
std::mt19937 randomGenerator(std::chrono::system_clock::now().time_since_epoch().count());

void toLower(std::wstring& string) {
    std::transform(string.begin(), string.end(), string.begin(),
        [](auto ch) {
            return std::towlower(ch);
        }
    );
}

std::size_t getRandomSizeTNumber(std::size_t from, std::size_t to) {
    std::uniform_int_distribution<std::size_t> distribution(from, to);
    return distribution(randomGenerator);
}

std::wstring str2wstr(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string wstr2str(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

std::string hexStr(unsigned char* data, int len)
{
    std::stringstream ss;
    ss << std::hex;

    for (std::size_t i = 0; i < len; ++i)
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

std::string md5(const std::string& str) {
    unsigned char* hashValue;
    hashValue = MD5(reinterpret_cast<const unsigned char *>(str.data()), str.length(), nullptr);
    return hexStr(hashValue, MD5_DIGEST_LENGTH);
}

std::wstring boolToStr(bool value) {
    return value ? L"Yes" : L"No";
}

std::string& trim(std::string& str)
{
    std::string whitSpaceChars = u8"\t\n\v\f\r ";
    return trimLeft(trimRight(str, whitSpaceChars), whitSpaceChars);
}

std::wstring& trim(std::wstring& str)
{
    std::wstring whitSpaceChars = L"\t\n\v\f\r ";
    return trimLeft(trimRight(str, whitSpaceChars), whitSpaceChars);
}

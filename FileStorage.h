//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_FILESTORAGE_H
#define MARKOV_FILESTORAGE_H

#include "consts.h"
#include <string>
#include <utility>
#include <vector>
#include <regex>

class FileStorage {
public:
    explicit FileStorage(std::string directory, std::string urlListFileName = ""):
            directory(std::move(directory)), urlListFileName(std::move(urlListFileName)), urlRegex(URL_PATTERN)
    {
    }

    FileStorage(const FileStorage& storage) = default;
    FileStorage(FileStorage&& storage) = default;
    FileStorage& operator = (const FileStorage& storage) = default;
    FileStorage& operator = (FileStorage&& storage) = default;

    [[nodiscard]] std::size_t downloadAllFiles() const;

    void deleteAllFiles() const;

    [[nodiscard]] std::vector<std::wstring> getAllFileNames() const;

    [[nodiscard]] bool hasAnyNoneEmptyFile() const;

private:
    std::string directory;
    std::string urlListFileName;
    std::wregex urlRegex;

    [[nodiscard]] bool isValidUrl(const std::wstring& url) const;

    [[nodiscard]] bool downloadFile(const std::wstring& url, std::string& downloadedFileName) const;
};


#endif //MARKOV_FILESTORAGE_H

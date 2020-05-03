//
// Created by datas on 4/28/2020.
//

#include "FileStorage.h"
#include "exceptions/FileNotFoundException.h"
#include "helpers.h"
#include "consts.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <regex>

std::size_t FileStorage::downloadAllFiles() const {
    std::size_t downloadedFilesCount = 0;

    std::wifstream inp;
    std::string downloadedFileName;

    try {
        inp.open(urlListFileName);
        if (!inp.is_open()) {
            throw FileNotFoundException(std::string(u8"Error! Urls file \"") + urlListFileName + u8"\" was not found!");
        }

        std::wstring line;
        while (std::getline(inp, line)) {
            line = trim(line);
            if (line.empty() || line[0] == COMMENT_CHAR_FOR_URLS_LIST_FILE)
                continue;

            if (!isValidUrl(line)) {
                std::wcerr << L"Warning! Skipped invalid url \"" << line << L"\"!" << std::endl;
            } else {
                if (!downloadFile(line, downloadedFileName)) {
                    std::wcout << L"  Warning! File from \"" << line << L"\" was not downloaded (skipped)!" << std::endl;
                } else {
                    std::wcout << L"  \"" << line << L"\" was successfully downloaded!" << std::endl;
                    std::wcout << L"    saved to " << std::filesystem::absolute(downloadedFileName).wstring() << std::endl;
                    ++downloadedFilesCount;
                }
            }
        }
    } catch (const std::wifstream::failure& e) {
        throw;
    }
    return downloadedFilesCount;
}

void FileStorage::deleteAllFiles() const {
    try {
        std::filesystem::directory_entry storageDirectory(directory);
        if (storageDirectory.exists()) {
            std::filesystem::remove_all(std::filesystem::path(directory));
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::wcerr << e.what() << std::endl;
    }
}

bool FileStorage::isValidUrl(const std::wstring& url) const {
    return std::regex_match(url, urlRegex);
}


bool FileStorage::downloadFile(const std::wstring &url, std::string& downloadedFileName) const {
    downloadedFileName = "";

    std::string command = std::string(u8"curl -k -L -s --connect-timeout ") + std::to_string(CURL_CONNECT_TIMEOUT) +
                          u8" --max-filesize " + std::to_string(CURL_MAX_FILE_SIZE) + u8" \"" + wstr2str(url) + u8"\"";
    std::FILE* pipe = popen(command.c_str(), u8"r");
    if (!pipe) {
        std::wcerr << L"Error! Cannot start curl process with command \"" << str2wstr(command) << L"\"!" << std::endl;
        return false;
    }

    std::array<char, MAX_CURL_PIPE_BUFFER_SIZE> buffer {};
    std::string fileContent;
    bool isFirstString = true;
    while (fgets(buffer.data(), MAX_CURL_PIPE_BUFFER_SIZE, pipe) != nullptr) {
        fileContent += buffer.data();
        if (isFirstString) {
            isFirstString = false;
            std::string firstLoweredChars = fileContent.substr(0, std::min<std::size_t>(fileContent.size(),
                                                                                             FIRST_CHARS_COUNT_TO_CHECK_HTML_RESPONSE));
            if (firstLoweredChars.find(u8"<!doctype") != std::string::npos ||
                firstLoweredChars.find(u8"<html>") != std::string::npos) {
                std::wcerr << L"Error! Url \"" << url << L"\" refers to HTML page!" << std::endl;
                return false;
            }
        }
    }

    int returnCode = pclose(pipe);

    if (returnCode == 28) {
        std::wcerr << L"Warning! Timeout occurred while downloading url \"" << url << "\"!" << std::endl;
        return false;
    }
    if (returnCode != 0) {
        std::wcerr << L"Warning! Curl for url \"" << url << L"\" finished with nonzero return code " << returnCode << L"!" << std::endl;
        return false;
    }

    try {
        std::filesystem::path storagePath(directory);
        std::string fileName = md5(fileContent);
        std::filesystem::path combinedFilePath = storagePath / fileName;
        downloadedFileName = combinedFilePath.generic_string();
        if (!std::filesystem::directory_entry(storagePath).exists()) {
            std::filesystem::create_directory(storagePath);
        }

        if (!std::filesystem::exists(combinedFilePath)) {
            try {
                std::ofstream out(downloadedFileName);
                if (!out.is_open()) {
                    std::wcerr << L"Warning! Cannot save url data (\"" << url << L"\") to file \""
                               << combinedFilePath << L"\"!" << std::endl;
                }
                out << fileContent << std::endl;
            } catch (const std::wofstream::failure& e) {
                throw;
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::wcerr << e.what() << std::endl;
        return false;
    }
    return true;
}

std::vector<std::wstring> FileStorage::getAllFileNames() const {
    std::vector<std::wstring> fileNames;
    std::filesystem::path storagePath(directory);

    if (std::filesystem::directory_entry(storagePath).exists()) {
        for (const auto& entry : std::filesystem::directory_iterator(storagePath)) {
            if (entry.is_regular_file() && entry.exists())
                fileNames.push_back(entry.path().wstring());
        }
    }
    return fileNames;
}

bool FileStorage::hasAnyNoneEmptyFile() const {
    std::vector<std::wstring> fileNames;
    std::filesystem::path storagePath(directory);
    if (!std::filesystem::directory_entry(storagePath).exists())
        return false;

    for (const auto& entry : std::filesystem::directory_iterator(storagePath)) {
        if (entry.is_regular_file() && entry.exists() && entry.file_size() > 0)
            return true;
    }
    return false;
}

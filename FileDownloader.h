//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_FILEDOWNLOADER_H
#define MARKOV_FILEDOWNLOADER_H

#include <string>

class FileDownloader {
public:
    FileDownloader(const std::string& pathToStoreFiles):
        pathToStoreFiles(pathToStoreFiles)
    {
    }

    bool download(const std::string& url) {
        return true; //TODO it is a stub
    }

private:
    std::string pathToStoreFiles;

};


#endif //MARKOV_FILEDOWNLOADER_H

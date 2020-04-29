//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_FILEHASLESSWORDSEXCEPTION_H
#define MARKOV_FILEHASLESSWORDSEXCEPTION_H

#include <bits/exception.h>
#include <string>

class FileHasLessWordsException : virtual public std::exception {
public:
    explicit FileHasLessWordsException(std::string message):
            message(std::move(message))
    {
    }

    [[nodiscard]]
    const char * what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};



#endif //MARKOV_FILEHASLESSWORDSEXCEPTION_H

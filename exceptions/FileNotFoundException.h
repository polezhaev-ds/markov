//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_FILENOTFOUNDEXCEPTION_H
#define MARKOV_FILENOTFOUNDEXCEPTION_H

#include <bits/exception.h>
#include <string>

class FileNotFoundException : virtual public std::exception {
public:
    explicit FileNotFoundException(std::string message):
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


#endif //MARKOV_FILENOTFOUNDEXCEPTION_H

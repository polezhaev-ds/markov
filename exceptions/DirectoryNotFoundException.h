//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_DIRECTORYNOTFOUNDEXCEPTION_H
#define MARKOV_DIRECTORYNOTFOUNDEXCEPTION_H

#include <bits/exception.h>
#include <string>

class DirectoryNotFoundException : virtual public std::exception {
public:
    explicit DirectoryNotFoundException(std::string message):
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

#endif //MARKOV_DIRECTORYNOTFOUNDEXCEPTION_H

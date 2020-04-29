//
// Created by datas on 4/28/2020.
//

#ifndef MARKOV_STARTINGTEXTHASLESSWORDSEXCEPTION_H
#define MARKOV_STARTINGTEXTHASLESSWORDSEXCEPTION_H

#include <bits/exception.h>
#include <string>

class StartingTextHasLessWordsException : virtual public std::exception {
public:
    explicit StartingTextHasLessWordsException(std::string message):
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


#endif //MARKOV_STARTINGTEXTHASLESSWORDSEXCEPTION_H

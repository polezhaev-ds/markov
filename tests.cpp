//
// Created by datas on 03.05.2020.
//

#define CATCH_CONFIG_MAIN

#include "external/catch.hpp"
#include "MarkovGenerator.h"
#include "exceptions/FileHasLessWordsException.h"

TEST_CASE(u8"Test class MarkovGenerator") {

    SECTION(u8"Check that order of Markov chain is set correctly") {
        std::size_t markovChainOrder = 2;
        MarkovGenerator generator(markovChainOrder);
        CHECK( generator.getOrder() == markovChainOrder );
    }

    SECTION(u8"Check zero order of Markov chain") {
        std::size_t markovChainOrder = 0;
        CHECK_THROWS_AS(MarkovGenerator(markovChainOrder), std::invalid_argument);
        CHECK_THROWS_WITH( MarkovGenerator(markovChainOrder),
                Catch::Contains(u8"Error! Invalid argument order! It should be greater than zero!") );
    }

    SECTION(u8"Check when input vector for training has not enough words") {
        std::size_t markovChainOrder = 2;
        MarkovGenerator generator(markovChainOrder);
        CHECK_THROWS_AS(generator.train({}), FileHasLessWordsException);
        CHECK_THROWS_WITH(generator.train({}),
                Catch::Contains(u8"File has 0 word(s) that is less than 3"));
    }

    SECTION(u8"Check when input vector for training has enough words") {
        std::size_t markovChainOrder = 2;
        MarkovGenerator generator(markovChainOrder);
        CHECK_NOTHROW(generator.train({L"hello", L"world", L"the"}));
    }

    SECTION(u8"Check when input vector for training has enough words") {
        std::size_t markovChainOrder = 2;
        MarkovGenerator generator(markovChainOrder);
        generator.train({L"hello", L"world", L"my", L"planet"});
        CHECK( generator.generateText({L"hello", L"world"}, 0) == L"hello world");
        CHECK( generator.generateText({L"hello", L"world"}, 1) == L"hello world my");
        CHECK( generator.generateText({L"hello", L"world"}, 2) == L"hello world my planet");
        CHECK( generator.generateText({L"world", L"my"}, 0) == L"world my");
        CHECK( generator.generateText({L"world", L"my"}, 1) == L"world my planet");
    }

}




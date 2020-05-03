//
// Created by datas on 30.04.2020.
//

#ifndef MARKOV_CONSTS_H
#define MARKOV_CONSTS_H

#include <string>

const std::size_t MAX_CURL_PIPE_BUFFER_SIZE = 2 * 1024 * 1024;

extern const std::size_t FIRST_CHARS_COUNT_TO_CHECK_HTML_RESPONSE;
extern const std::size_t CURL_MAX_FILE_SIZE;
extern const std::size_t MAX_CURL_PIPE_BUFFER_SIZE;
extern const std::size_t CURL_MAX_FILE_SIZE;
extern const std::size_t CURL_CONNECT_TIMEOUT; // in seconds
extern const std::wstring URL_PATTERN;
extern const wchar_t COMMENT_CHAR_FOR_URLS_LIST_FILE;

// Command line options
extern const std::string COMMAND_OPTION_LONG;
extern const std::string COMMAND_OPTION_PAIR;
extern const std::string HELP_OPTION_LONG;
extern const std::string HELP_OPTION_PAIR;
extern const std::string STORAGE_DIRECTORY_OPTION_LONG;
extern const std::string STORAGE_DIRECTORY_OPTION_PAIR;
extern const std::string URL_LIST_FILE_OPTION_LONG;
extern const std::string URL_LIST_FILE_OPTION_PAIR;
extern const std::string CLEAR_DIRECTORY_OPTION_LONG;
extern const std::string CLEAR_DIRECTORY_OPTION_PAIR;
extern const std::string MARKOV_GENERATOR_ORDER_OPTION_LONG;
extern const std::string MARKOV_GENERATOR_ORDER_OPTION_PAIR;
extern const std::string MARKOV_GENERATOR_STATE_FILE_OPTION_LONG;
extern const std::string MARKOV_GENERATOR_STATE_FILE_OPTION_PAIR;
extern const std::string GENERATED_TEXT_LENGTH_OPTION_LONG;
extern const std::string GENERATED_TEXT_LENGTH_OPTION_PAIR;
extern const std::string STARTING_PHRASE_OPTION_LONG;
extern const std::string STARTING_PHRASE_OPTION_PAIR;
extern const std::string INCREMENTAL_TRAINING_OPTION_LONG;
extern const std::string INCREMENTAL_TRAINING_OPTION_PAIR;

// Default command line options
extern const std::string DEFAULT_DIRECTORY_NAME_TO_STORE_DOWNLOADED_FILES;
extern const std::string DEFAULT_URL_LIST_FILE_NAME;
extern const std::size_t DEFAULT_MARKOV_GENERATOR_ORDER;
extern const std::string DEFAULT_MARKOV_GENERATOR_STATE_FILE_NAME;
extern const bool DEFAULT_USE_INCREMENTAL_TRAINING;
extern const std::size_t DEFAULT_GENERATED_TEXT_SIZE;
extern const bool DEFAULT_DELETE_ALL_STORED_FILES;


#endif //MARKOV_CONSTS_H

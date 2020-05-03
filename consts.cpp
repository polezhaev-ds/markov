//
// Created by datas on 30.04.2020.
//

#include "consts.h"

const std::size_t FIRST_CHARS_COUNT_TO_CHECK_HTML_RESPONSE = 512 * 1024 * 1024;
const std::size_t CURL_MAX_FILE_SIZE = 256 * 1024 * 1024;

const std::size_t CURL_CONNECT_TIMEOUT = 10; // in seconds
const std::wstring URL_PATTERN = L"^(?:(?:https?)://)(?:\\S+(?::\\S*)?@)?(?:(?!10(?:\\.\\d{1,3}){3})(?!127(?:\\.\\d{1,3}){3})(?!169\\.254(?:\\.\\d{1,3}){2})(?!192\\.168(?:\\.\\d{1,3}){2})(?!172\\.(?:1[6-9]|2\\d|3[0-1])(?:\\.\\d{1,3}){2})(?:[1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])(?:\\.(?:1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}(?:\\.(?:[1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))|(?:(?:[-a-z\\u00a1-\\uffff0-9]+-?)*[-a-z\\u00a1-\\uffff0-9]+)(?:\\.(?:[-a-z\\u00a1-\\uffff0-9]+-?)*[-a-z\\u00a1-\\uffff0-9]+)*(?:\\.(?:[-a-z\\u00a1-\\uffff0-9]{2,})))(?::\\d{2,5})?(?:/[^\\s]*)?$";
const wchar_t COMMENT_CHAR_FOR_URLS_LIST_FILE = L'#';

// Command line options
const std::string COMMAND_OPTION_LONG = u8"command";
const std::string COMMAND_OPTION_PAIR = std::string(u8"c,command") + COMMAND_OPTION_LONG;
const std::string HELP_OPTION_LONG = u8"help";
const std::string HELP_OPTION_PAIR = std::string(u8"h,") + HELP_OPTION_LONG;
const std::string STORAGE_DIRECTORY_OPTION_LONG = u8"directory";
const std::string STORAGE_DIRECTORY_OPTION_PAIR = std::string(u8"d,") + STORAGE_DIRECTORY_OPTION_LONG;
const std::string URL_LIST_FILE_OPTION_LONG = u8"urls";
const std::string URL_LIST_FILE_OPTION_PAIR = std::string(u8"u,") + URL_LIST_FILE_OPTION_LONG;
const std::string CLEAR_DIRECTORY_OPTION_LONG = u8"clear";
const std::string CLEAR_DIRECTORY_OPTION_PAIR = std::string(u8"c,") + CLEAR_DIRECTORY_OPTION_LONG;
const std::string MARKOV_GENERATOR_ORDER_OPTION_LONG = u8"order";
const std::string MARKOV_GENERATOR_ORDER_OPTION_PAIR = std::string(u8"n,") + MARKOV_GENERATOR_ORDER_OPTION_LONG;
const std::string MARKOV_GENERATOR_STATE_FILE_OPTION_LONG = u8"file";
const std::string MARKOV_GENERATOR_STATE_FILE_OPTION_PAIR = std::string(u8"f,") + MARKOV_GENERATOR_STATE_FILE_OPTION_LONG;
const std::string GENERATED_TEXT_LENGTH_OPTION_LONG = u8"length";
const std::string GENERATED_TEXT_LENGTH_OPTION_PAIR = std::string(u8"l,") + GENERATED_TEXT_LENGTH_OPTION_LONG;
const std::string STARTING_PHRASE_OPTION_LONG = u8"text";
const std::string STARTING_PHRASE_OPTION_PAIR = std::string(u8"t,") + STARTING_PHRASE_OPTION_LONG;
const std::string INCREMENTAL_TRAINING_OPTION_LONG = u8"incremental";
const std::string INCREMENTAL_TRAINING_OPTION_PAIR = std::string(u8"i,") + INCREMENTAL_TRAINING_OPTION_LONG;


// Default command line options
const std::string DEFAULT_DIRECTORY_NAME_TO_STORE_DOWNLOADED_FILES = u8"downloaded";
const std::string DEFAULT_URL_LIST_FILE_NAME = u8"urls.list";
const std::size_t DEFAULT_MARKOV_GENERATOR_ORDER = 2;
const std::string DEFAULT_MARKOV_GENERATOR_STATE_FILE_NAME = u8"markov.state";
const bool DEFAULT_USE_INCREMENTAL_TRAINING = false;
const std::size_t DEFAULT_GENERATED_TEXT_SIZE = 10;
const bool DEFAULT_DELETE_ALL_STORED_FILES = false;

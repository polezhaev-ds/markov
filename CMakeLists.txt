cmake_minimum_required(VERSION 3.15)
project(markov)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

add_executable(markov main.cpp MarkovGenerator.cpp MarkovGenerator.h MarkovSelector.cpp MarkovSelector.h helpers.cpp helpers.h FileStorage.cpp FileStorage.h parse_file.cpp parse_file.h exceptions/FileNotFoundException.h exceptions/FileHasLessWordsException.h exceptions/StartingTextHasLessWordsException.h exceptions/DirectoryNotFoundException.h consts.cpp consts.h commands.cpp commands.h)
add_executable(markov_test tests.cpp MarkovGenerator.cpp MarkovGenerator.h MarkovSelector.cpp MarkovSelector.h helpers.cpp helpers.h FileStorage.cpp FileStorage.h parse_file.cpp parse_file.h exceptions/FileNotFoundException.h exceptions/FileHasLessWordsException.h exceptions/StartingTextHasLessWordsException.h exceptions/DirectoryNotFoundException.h consts.cpp consts.h commands.cpp commands.h)
target_link_libraries(${PROJECT_NAME}  stdc++fs)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)

target_link_libraries(markov_test  stdc++fs)
target_link_libraries(markov_test OpenSSL::Crypto)
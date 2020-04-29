cmake_minimum_required(VERSION 3.15)
project(markov)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(markov main.cpp MarkovGenerator.cpp MarkovGenerator.h MarkovSelector.cpp MarkovSelector.h helpers.cpp helpers.h FileDownloader.cpp FileDownloader.h parse_file.cpp parse_file.h exceptions/FileNotFoundException.h exceptions/FileHasLessWordsException.h exceptions/StartingTextHasLessWordsException.h exceptions/DirectoryNotFoundException.h)
#target_link_libraries(markov stdc++fs)
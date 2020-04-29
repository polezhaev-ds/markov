#include <iostream>
#include <vector>
#include <chrono>
#include <random>
//#include <filesystem>
#include "parse_file.h"
#include "exceptions/FileNotFoundException.h"
#include "exceptions/DirectoryNotFoundException.h"
#include "MarkovGenerator.h"
#include "helpers.h"
#include "external/argparse.h"


// markov download <url_list_file> [<dir>]
// markov train [<dir>] [-n 3] [-s <file>]
// markov generate "hello real world" [-l 10] [-s <file>]
// default dir ./downlod
// default n 2
// default l 10
// default s markov_state

//void trainMarkovGeneratorOnAllFilesInDirectory(const std::string& directoryPath, MarkovGenerator& generator) {
//    if (!std::filesystem::exists(directoryPath)) {
//        throw DirectoryNotFoundException(std::string("\'") + directoryPath + "\' was not found");
//    }
//    std::vector<std::string> text;
//
//    for (auto& entry : std::filesystem::directory_iterator(directoryPath.c_str())) {
//        try {
//            if (entry.is_regular_file()) {
//                //text = parseFile(entry.path().u8string());
//                generator.train(text);
//            }
//        }
//        catch (const FileNotFoundException &e) {
//            std::cout << e.what() << " It was skipped!" << std::endl;
//        }
//        catch (const std::filesystem::filesystem_error& e) {
//            std::cout << e.what() << std::endl;
//            break;
//        }
//    }
//}

int main(int argc, char* argv[]) {

//    ArgumentParser parser("Markov text generator of n-th order");
//    parser.add_argument("-t", "--train", "Download files and train model");

    for (std::size_t i = 0; i < 10; ++i)
        std::cout << getRandomSizeTNumber(0, 1) << " " << std::endl;
    std::setlocale(LC_ALL, "en_US.UTF-8");
    try {
        std::size_t chainSize = 3;
        MarkovGenerator generator(chainSize);
        //std::vector<std::string> text = parseFile("1.txt");
        std::vector<std::string> text = parseFile("2600-0.txt");
        generator.train(text);
        std::cout << generator.generateText({"sometimes", "it", "occurred"}, 200) << std::endl;
    } catch (const FileNotFoundException& e) {
        std::cout << e.what() << " It was skipped!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception has occurred!" << std::endl;
    }

    return 0;
}

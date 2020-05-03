#include "commands.h"
#include <iostream>

int main(int argc, char* argv[]) {

    std::setlocale(LC_ALL, "");

    try {
        parseAndProcessCommand(argc, argv);
    }  catch (const std::exception& e) {
        std::wcout << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::wcout << L"Error! Unknown exception has occurred!" << std::endl;
        return 1;
    }

    return 0;
}

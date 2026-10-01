#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "wordCounter.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    if (args.size() < 3) {
        std::cout << "wrong number of arguments" << "\n";
        return 1;
    }
    try {
        const WordCounter OBJ(args[1]);
        OBJ.sentToFile(args[2]);
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

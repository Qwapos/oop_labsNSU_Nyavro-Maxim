#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "wordCounter.h"
#include "FileReader.h"
#include "CSVWriter.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    if (args.size() < 3) {
        std::cout << "wrong number of arguments" << "\n";
        return 1;
    }
    try {
        FileReader reader(args[1]);
        WordCounter counter;
        CSVWriter writer(args[2]);
        std::string word;
        while (reader.readWord(word))
        {
            counter.addWord(word);
        }
        writer.writeCSV(counter.getSorted(), counter.getTotal());
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

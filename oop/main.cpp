#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <cstddef>
#include "wordCounter.h"
#include "FileReader.h"
#include "CSVWriter.h"

constexpr std::size_t REQUIRED_ARG_COUNT = 3;
constexpr std::size_t INPUT_FILE_ARG_INDEX = 1;
constexpr std::size_t OUTPUT_FILE_ARG_INDEX = 2;



int main(int argc, char *argv[]) {
    auto *begin = argv;
    auto *end = begin + argc; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    std::vector<std::string> args(begin, end);
    if (args.size() < REQUIRED_ARG_COUNT) {
        std::cerr << "error: wrong number of arguments" << "\n";
        return 1;
    }
    try {
        FileReader reader(args.at(INPUT_FILE_ARG_INDEX));
        WordCounter counter;
        CSVWriter writer(args.at(OUTPUT_FILE_ARG_INDEX));
        std::string word;
        while (reader.readWord(word))
        {
            counter.addWord(word);
        }
        writer.writeCSV(counter.getFrequencies());
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

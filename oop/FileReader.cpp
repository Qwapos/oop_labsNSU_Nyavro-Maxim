#include "FileReader.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <cctype>

FileReader::FileReader(const std::string& sourceFileName)
{
    fin = std::ifstream(sourceFileName);
    if (!fin.is_open())
    {
        throw std::runtime_error("can't open input file: " + sourceFileName);
    }
}



bool FileReader::readWord(std::string& word)
{
    word.clear();
    char c = 0;
    while (fin.get(c))
    {
        const auto UC = static_cast<unsigned char> (c);
        if (std::isalnum(UC) != 0)
        {
            word.push_back(c);
        }
        else if (!word.empty())
        {
            break;
        }
    }
    return !word.empty();
}

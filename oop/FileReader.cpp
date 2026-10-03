#include "FileReader.h"
#include <fstream>
#include <string>


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
    return static_cast<bool> (fin >> word);
}

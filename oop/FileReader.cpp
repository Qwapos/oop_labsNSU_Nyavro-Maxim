#include "FileReader.h"
#include <fstream>
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
    bool flag = false;
    char c = 0;
    while (fin >> c)
    {
        if (isalnum(c) != 0)
        {
            word.push_back(c);
            flag = true;
        }
        else if (flag)
        {
            break;
        }
    }
    return flag;
}

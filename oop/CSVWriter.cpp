#include "CSVWriter.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "wordFrequency.h"

CSVWriter::CSVWriter(const std::string& fileName)
{
    fout = std::ofstream(fileName);
    if (!fout.is_open())
    {
        throw std::runtime_error("can't open output file: " + fileName);
    }
}


void CSVWriter::writeCSV(const std::vector<WordFrequency>& data)
{
    for (const auto& it : data)
    {
        fout << it.word << "," << it.count << "," << it.percent << "\n";
    }
}

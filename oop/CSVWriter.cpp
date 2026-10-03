#include "CSVWriter.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility>


CSVWriter::CSVWriter(const std::string& fileName)
{
    fout = std::ofstream(fileName);
    if (!fout.is_open())
    {
        throw std::runtime_error("can't open output file: " + fileName);
    }
}


void CSVWriter::writeCSV(const std::vector<std::pair<std::string, long long>>& data, long long totalWords)
{
    for (const auto& it : data)
    {
        const double FREQ = static_cast<double> (it.second) * 100.0 / static_cast<double>(totalWords);
        fout << it.first << "," << it.second << "," << FREQ << "\n";
    }
}

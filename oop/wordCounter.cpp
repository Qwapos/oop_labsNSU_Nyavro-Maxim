#include "wordCounter.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace {
    bool cmp(const std::pair<std::string, long long> &a,
             const std::pair<std::string, long long> &b) {
        if (a.second < b.second) {
            return false;
        }
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return true;
    }
}

WordCounter::WordCounter(const std::string &sourceFileName)
{
    std::ifstream fin(sourceFileName);
    if (!fin.is_open())
    {
        throw std::runtime_error("can't open input file: " + sourceFileName);
    }
    std::string element;
    while (fin >> element) {
        words[element]++;
        wordsCount++;
    }
    if (wordsCount == 0) {
        throw std::runtime_error("input file is empty: " + sourceFileName);;
    }
}

void WordCounter::sentToFile(const std::string &outputFileName) const {
    std::vector<std::pair<std::string, long long> > sorted(words.begin(), words.end());
    std::sort(sorted.begin(), sorted.end(), cmp);
    std::ofstream fout(outputFileName);
    if (!fout.is_open())
    {
        throw std::runtime_error("can't open output file: " + outputFileName);
    }
    for (auto &it: sorted) {
        const double FREQ = static_cast<double>(it.second) * 100.0 / static_cast<double>(wordsCount);
        fout << it.first << "," << it.second << "," << FREQ << "\n";
    }
}

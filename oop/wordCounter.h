#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H
#include <map>
#include <vector>
#include <string>
#include <utility>
#include "wordFrequency.h"

class WordCounter {
public:
    void addWord(const std::string& word);
    std::vector<WordFrequency> getFrequencies() const;
private:
    std::map<std::string, long long> words;
    long long totalWords = 0;
};
#endif

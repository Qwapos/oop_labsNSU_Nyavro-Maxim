#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H
#include <map>
#include <vector>
#include <string>
#include <utility>

class WordCounter {
public:
    void addWord(const std::string& word);
    std::vector<std::pair<std::string, long long>> getSorted() const;
    long long getTotal() const;
private:
    std::map<std::string, long long> words;
    long long totalWords = 0;
};
#endif

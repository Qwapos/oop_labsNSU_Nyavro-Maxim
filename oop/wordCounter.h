#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H
#include <map>
#include <string>

class WordCounter {
public:
    explicit WordCounter(const std::string& sourceFileName);

    void sentToFile(const std::string& outputFileName)const;

private:
    std::map<std::string, long long> words;
    long long wordsCount = 0;
};
#endif

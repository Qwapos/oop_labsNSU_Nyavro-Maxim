
#ifndef WORD_FREQUENCY_H
#define WORD_FREQUENCY_H
#include <string>

struct WordFrequency
{
    std::string word;
    long long count = 0;
    double percent = 0.0;
};


#endif //WORD_FREQUENCY_H

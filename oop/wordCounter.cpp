#include "wordCounter.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

void WordCounter::addWord(const std::string& word)
{
    words[word]++;
    totalWords++;
}

std::vector<std::pair<std::string, long long>> WordCounter::getSorted() const
{
    std::vector<std::pair<std::string, long long>> result;

    result.reserve(words.size());

    for (const auto& word : words)
    {
        result.emplace_back(word.first, word.second);
    }
    std::sort(result.begin(), result.end(),
              [](const auto& a, const auto& b) {
                  if (a.second != b.second) {
                      return a.second > b.second;
                  }
                  return a.first < b.first;
              });
    return result;
}

long long WordCounter::getTotal() const
{
    return totalWords;
}

#include "wordCounter.h"
#include "wordFrequency.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

void WordCounter::addWord(const std::string& word)
{
    words[word]++;
    totalWords++;
}

std::vector<WordFrequency> WordCounter::getFrequencies() const
{
    std::vector<WordFrequency> result;
    result.reserve(words.size());
    for (const auto& word : words)
    {
        const auto PERCENT = static_cast<double>(word.second) * 100.0 / static_cast<double>(totalWords);
        result.push_back({word.first, word.second, PERCENT});
    }
    std::sort(result.begin(), result.end(),
              [](const auto& a, const auto& b) {
                  if (a.count != b.count) {
                      return a.count > b.count;
                  }
                  return a.word < b.word;
              });
    return result;
}

#include "trie.h"

#include <algorithm>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

void Trie::insert(std::string_view word)
{
    Node* current = &root_;
    for (const auto CH: word)
    {
        const auto KEY = static_cast<unsigned char> (CH);
        auto& child = current->children[KEY];
        if (!child)
        {
            child = std::make_unique<Node>();
        }
        current = child.get();
    }
    if (!current->is_terminal)
    {
        current->is_terminal = true;
        size_++;
    }
}

bool Trie::contains(std::string_view word) const
{
    const Node* current = &root_;
    for (const auto CH: word)
    {
        const auto KEY = static_cast<unsigned char> (CH);
        if (!current->children.contains(KEY)) {
            return false;
        }
        current = current->children.find(KEY)->second.get();
    }
    return current->is_terminal;
}

Trie::size_type Trie::size() const
{
    return size_;
}

bool Trie::empty() const
{
    return size_ == 0;
}

bool Trie::erase(std::string_view word)
{
    std::vector<std::pair<Node*, unsigned char>> trace;
    Node* current = &root_;
    for (const auto CH: word)
    {
        const auto KEY = static_cast<unsigned char> (CH);
        if (!current->children.contains(KEY))
            {
                return false;
            }
        trace.emplace_back (current, KEY);
        current = current->children.find(KEY)->second.get();
    }
    if (!current->is_terminal)
    {
        return false;
    }
    current->is_terminal = false;
    size_--;
    while (current->children.empty() && current != &root_ && !current->is_terminal)
    {
        unsigned char key{};
        std::tie (current, key) =  trace.back();
        trace.pop_back();
        current->children.erase(key);
    }
    return true;
}
Trie::size_type Trie::prefix_count(std::string_view pref) const
{
    const Node* current = &root_;
    size_type prefix = 0;
    for (const auto CH: pref)
    {
        auto key = static_cast<unsigned char> (CH);
        if (!current->children.contains(key))
        {
            return prefix;
        }
        current = current->children.find(key)->second.get();
    }
    std::vector<const Node*> dfsChildren;
    dfsChildren.emplace_back(current);
    while (!dfsChildren.empty())
    {
        current = dfsChildren.back();
        dfsChildren.pop_back();
        if (current->is_terminal) {
            prefix++;
        }
        for (const auto& child : current->children)
        {
            dfsChildren.emplace_back(child.second.get());
        }
    }
    return prefix;
}

// NOLINTNEXTLINE(misc-no-recursion)
void Trie::collectWords (const Node& node,
                         std::string& current,
                         std::vector<std::string>& result,
                         size_type limit) {
    if (limit != 0 && result.size() >= limit)
    {
        return;
    }

    if (node.is_terminal)
    {
        result.emplace_back(current);

        if (limit != 0 && result.size() >= limit)
        {
            return;
        }
    }
    for (const auto& child : node.children)
    {
        current += static_cast<char> (child.first);
        collectWords(*child.second, current, result, limit);
        current.pop_back();
        if (limit != 0 && result.size() >= limit)
        {
            return;
        }
    }
}

std::vector<std::string> Trie::words_with_prefix(std::string_view pref, size_type limit) const
{
    const Node* current = &root_;
    std::vector<std::string> result;
    for (const auto CH: pref)
    {
        auto key = static_cast<unsigned char> (CH);
        if (!current->children.contains(key))
        {
            return result;
        }
        current = current->children.find(key)->second.get();
    }
    std::string buffer (pref);
    collectWords(*current, buffer, result, limit);
    return result;
}

void Trie::clear() {
    root_ = Node{};
    size_ = 0;
}
Trie::Trie(const Trie& other)
{
    for (const auto& word: other.words_with_prefix(""))
    {
        insert(word);
    }
}
void Trie::swap(Trie& other) noexcept
{
    using std::swap;
    swap(root_, other.root_);
    swap(size_, other.size_);
}

Trie& Trie::operator=(const Trie& other)
{
    if (this != &other)
    {
        Trie temp = other;
        swap(temp);
    }
    return *this;
}
Trie::Trie(Trie&& other) noexcept
{
    swap(other);
}
Trie& Trie::operator=(Trie&& other) noexcept
{
    if (this != &other)
    {
        Trie temp = std::move(other);
        swap(temp);
    }
    return *this;
}
bool Trie::operator==(const Trie& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    return std::ranges::all_of(
    words_with_prefix(""),
    [&other](const std::string& word)
    {
        return other.contains(word);
    });
}
bool Trie::operator!=(const Trie& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Trie& trie)
{
    for (const auto& word: trie.words_with_prefix(""))
    {
        os << word << '\n';
    }
    return os;
}

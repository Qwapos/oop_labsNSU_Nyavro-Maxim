#include <iostream>
#include "trie.h"

int main()
{
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("cart");
    trie.insert("dog");
    trie.insert("");

    std::cout << "ca:    " << trie.prefix_count("ca") << '\n';    // 3
    std::cout << "cat:   " << trie.prefix_count("cat") << '\n';   // 1
    std::cout << "car:   " << trie.prefix_count("car") << '\n';   // 2
    std::cout << "cart:  " << trie.prefix_count("cart") << '\n';  // 1
    std::cout << "d:     " << trie.prefix_count("d") << '\n';     // 1
    std::cout << "x:     " << trie.prefix_count("x") << '\n';     // 0
    std::cout << "cx:    " << trie.prefix_count("cx") << '\n';    // 0
    std::cout << "empty: " << trie.prefix_count("") << '\n';      // 5
    std::cout << "size:  " << trie.size() << '\n';                // 5
}
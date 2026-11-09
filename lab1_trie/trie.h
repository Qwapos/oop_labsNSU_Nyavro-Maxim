#ifndef TRIE_H
#define TRIE_H
#include <cstddef>
#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>


// Контракт:
// - пустая строка — валидное слово;
// - дубликаты не хранятся, повторный insert ничего не меняет;
// - erase возвращает true, только если слово было;
// - prefix_count включает слово, совпадающее с префиксом;
// - words_with_prefix(..., 0) — без ограничения, порядок алфавитный;
// - operator== сравнивает множества строк;
// - operator<< печатает по одному слову на строку.

class Trie
{
public:
    using size_type = std::size_t;

    Trie() = default;
    ~Trie() = default;

    Trie(const Trie& other);               // Конструктор копирования
    Trie(Trie&& other) noexcept;           // Конструктор перемещения

    Trie& operator=(const Trie& other);    // Оператор присваивания копированием
    Trie& operator=(Trie&& other) noexcept;// Оператор присваивания перемещением

    // --- базовые методы ---
    void insert(std::string_view word);       // Вставка строки
    [[nodiscard]] bool contains(std::string_view word) const;  // Проверка наличия строки
    bool erase(std::string_view word);        // Удаление строки
    [[nodiscard]] size_type prefix_count(std::string_view pref) const; // Количество слов с данным префиксом

    [[nodiscard]] std::vector<std::string> words_with_prefix(
        std::string_view pref, size_type limit = 0) const; // Все слова с данным префиксом

    // --- служебные методы ---
    void clear();                          // Очистка дерева
    [[nodiscard]] bool empty() const;                    // true, если нет слов
    [[nodiscard]] size_type size() const;                // Количество сохранённых слов

    // --- перегрузка операторов ---
    bool operator==(const Trie& other) const; // Равенство по множеству строк
    bool operator!=(const Trie& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Trie& trie);
    // Красивый вывод всех слов в алфавитном порядке

private:

    struct Node
    {
        std::map<unsigned char, std::unique_ptr<Node>> children;
        bool is_terminal   = false;
    };

    Node root_;
    size_type size_ = 0;
    static void collectWords(const Node& node,
                             std::string& current,
                             std::vector<std::string>& result,
                             size_type limit);
    void swap(Trie& other) noexcept;
};






#endif
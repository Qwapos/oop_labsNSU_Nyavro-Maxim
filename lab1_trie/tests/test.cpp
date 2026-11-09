#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "trie.h"

class TrieTest : public ::testing::Test
{
protected:
    Trie trie;

    void SetUp() override
    {
        trie.insert("cat");
        trie.insert("car");
        trie.insert("cart");
        trie.insert("dog");
        trie.insert("");
    }
};

TEST(TrieEmptyTest, NewTrieIsEmpty)
{
    const Trie trie;

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), Trie::size_type{0});
    EXPECT_FALSE(trie.contains(""));
    EXPECT_FALSE(trie.contains("cat"));
    EXPECT_EQ(trie.prefix_count(""), Trie::size_type{0});
    EXPECT_TRUE(trie.words_with_prefix("").empty());
}

TEST_F(TrieTest, InsertAndContains)
{
    EXPECT_EQ(trie.size(), 5);
    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_TRUE(trie.contains("car"));
    EXPECT_TRUE(trie.contains("cart"));
    EXPECT_TRUE(trie.contains("dog"));
    EXPECT_TRUE(trie.contains(""));

    EXPECT_FALSE(trie.contains("ca"));
    EXPECT_FALSE(trie.contains("cats"));
    EXPECT_FALSE(trie.contains("dragon"));
}

TEST_F(TrieTest, DuplicateInsertDoesNotChangeSize)
{
    trie.insert("cat");
    trie.insert("car");
    trie.insert("");

    EXPECT_EQ(trie.size(), 5);
}

TEST_F(TrieTest, EraseLeaf)
{
    EXPECT_TRUE(trie.erase("dog"));
    EXPECT_FALSE(trie.contains("dog"));
    EXPECT_EQ(trie.size(), 4);
    EXPECT_EQ(trie.prefix_count("d"), 0);
}

TEST_F(TrieTest, EraseWordWithChildren)
{
    EXPECT_TRUE(trie.erase("car"));
    EXPECT_FALSE(trie.contains("car"));
    EXPECT_TRUE(trie.contains("cart"));
    EXPECT_EQ(trie.size(), 4);
    EXPECT_EQ(trie.prefix_count("car"), 1);
}

TEST_F(TrieTest, EraseMissingWord)
{
    EXPECT_FALSE(trie.erase("dragon"));
    EXPECT_EQ(trie.size(), 5);
}

TEST_F(TrieTest, EraseEmptyWord)
{
    EXPECT_TRUE(trie.erase(""));
    EXPECT_FALSE(trie.contains(""));
    EXPECT_EQ(trie.size(), 4);
}

TEST_F(TrieTest, PrefixCount)
{
    EXPECT_EQ(trie.prefix_count(""), 5);
    EXPECT_EQ(trie.prefix_count("c"), 3);
    EXPECT_EQ(trie.prefix_count("ca"), 3);
    EXPECT_EQ(trie.prefix_count("car"), 2);
    EXPECT_EQ(trie.prefix_count("cart"), 1);
    EXPECT_EQ(trie.prefix_count("cat"), 1);
    EXPECT_EQ(trie.prefix_count("d"), 1);
    EXPECT_EQ(trie.prefix_count("x"), 0);
    EXPECT_EQ(trie.prefix_count("cx"), 0);
}

TEST_F(TrieTest, WordsWithPrefix)
{
    const std::vector<std::string> expected{
        "", "car", "cart", "cat", "dog"
    };

    EXPECT_EQ(trie.words_with_prefix(""), expected);
}

TEST_F(TrieTest, WordsWithPrefixLimit)
{
    const std::vector<std::string> expected{"car", "cart"};

    EXPECT_EQ(trie.words_with_prefix("ca", 2), expected);
    EXPECT_EQ(trie.words_with_prefix("ca", 1).size(), 1);
    EXPECT_EQ(trie.words_with_prefix("ca", 99).size(), 3);
    EXPECT_EQ(trie.words_with_prefix("ca", 0).size(), 3);
}

TEST_F(TrieTest, WordsWithPrefixThatIsAWord)
{
    const std::vector<std::string> expected{"car", "cart"};

    EXPECT_EQ(trie.words_with_prefix("car"), expected);
}

TEST_F(TrieTest, MissingPrefix)
{
    EXPECT_TRUE(trie.words_with_prefix("x").empty());
    EXPECT_EQ(trie.prefix_count("x"), 0);
}

TEST_F(TrieTest, CopyConstructorIsDeep)
{
    Trie copy(trie);
    trie.erase("cat");

    EXPECT_TRUE(copy.contains("cat"));
    EXPECT_FALSE(trie.contains("cat"));
    EXPECT_EQ(copy.size(), 5);
}

TEST_F(TrieTest, CopyAssignmentReplacesOldContents)
{
    Trie other;
    other.insert("dragon");

    other = trie;

    EXPECT_EQ(other, trie);
    EXPECT_FALSE(other.contains("dragon"));
}

TEST_F(TrieTest, SelfCopyAssignment)
{
    Trie& alias = trie;
    trie = alias;

    EXPECT_EQ(trie.size(), 5);
    EXPECT_TRUE(trie.contains("cat"));
}

TEST_F(TrieTest, MoveConstructor)
{
    Trie moved(std::move(trie));

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
    EXPECT_EQ(moved.size(), 5);
    EXPECT_TRUE(moved.contains("cat"));
}

TEST_F(TrieTest, MoveAssignment)
{
    Trie moved;
    moved.insert("dragon");

    moved = std::move(trie);

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(moved.size(), 5);
    EXPECT_TRUE(moved.contains("cat"));
    EXPECT_FALSE(moved.contains("dragon"));
}

TEST_F(TrieTest, Clear)
{
    trie.clear();

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
    EXPECT_FALSE(trie.contains("cat"));
    EXPECT_TRUE(trie.words_with_prefix("").empty());

    trie.insert("x");
    EXPECT_TRUE(trie.contains("x"));
    EXPECT_EQ(trie.size(), 1);
}

TEST(TrieEqualityTest, SameSetDifferentInsertionOrder)
{
    Trie first;
    first.insert("cat");
    first.insert("car");
    first.insert("");

    Trie second;
    second.insert("");
    second.insert("car");
    second.insert("cat");

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);

    second.insert("dog");

    EXPECT_FALSE(first == second);
    EXPECT_TRUE(first != second);
}

TEST_F(TrieTest, Output)
{
    std::ostringstream os;
    os << trie;

    EXPECT_EQ(os.str(), "\ncar\ncart\ncat\ndog\n");
}

TEST_F(TrieTest, Utf8Words)
{
    Trie utf8;
    utf8.insert("кот");
    utf8.insert("котёнок");
    utf8.insert("коты");

    const std::vector<std::string> expected{
        "кот", "коты", "котёнок"
    };

    EXPECT_EQ(utf8.size(), 3);
    EXPECT_TRUE(utf8.contains("кот"));
    EXPECT_EQ(utf8.prefix_count("кот"), 3);
    EXPECT_EQ(utf8.words_with_prefix("кот"), expected);
}
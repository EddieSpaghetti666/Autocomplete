#include <Autocompleter.h>
#include <Spellchecker.h>
#include <Trie.h>

#include <set>
#include <string>
#include <vector>

#include "gtest/gtest.h"

class AutocompleteTest : public ::testing::Test {
 public:
  void SetUp() override { ac.setDictionary(dictionary); }

 protected:
  Autocompleter ac;
  const std::vector<std::string> dictionary = {
      "Apple",       "Apricots",    "Avocado",    "Banana", "Blackberries",
      "Blueberries", "Cranberries", "Grapefruit", "Grapes"};
};
TEST_F(AutocompleteTest, emptyString) {
  ASSERT_EQ(ac.getAllStringsFor(std::string()).size(), dictionary.size());
}

TEST_F(AutocompleteTest, findWords) {
  EXPECT_EQ(ac.getAllStringsFor(std::string("Ap")).size(), 2);
  EXPECT_EQ(ac.getAllStringsFor(std::string("F")).size(), 0);
  EXPECT_EQ(ac.getAllStringsFor(std::string("Bl")).size(), 2);
  EXPECT_EQ(ac.getAllStringsFor(std::string("Gr")).size(), 2);
  EXPECT_EQ(ac.getAllStringsFor(std::string("Avocado")).size(), 1);
}

TEST_F(AutocompleteTest, wordsContain) {
  const auto words = ac.getAllStringsFor(std::string("Ap"));
  EXPECT_NE(std::find(words.begin(), words.end(), "Apricots"), words.end());
  EXPECT_EQ(std::find(words.begin(), words.end(), "Strawberries"), words.end());
}

TEST(TrieTestFind, findEmptyString) {
  Trie trie;

  ASSERT_TRUE(trie.find(""));
}
TEST(TrieTestFind, simpleInsert) {
  Trie trie;

  trie.insert("a");

  ASSERT_TRUE(trie.find("a"));
}

TEST(TrieTestFind, shouldNotFind) {
  Trie trie;

  trie.insert("hello");

  ASSERT_FALSE(trie.find("world"));
}

TEST(TrieTestFind, emptyInsert) {
  Trie trie;

  trie.insert("");

  ASSERT_TRUE(trie.find(""));
}

TEST(TrieTestFind, longerInsert) {
  Trie trie;

  trie.insert("hello");

  ASSERT_TRUE(trie.find("hello"));
}

TEST(TrieTestFind, multipleInserts) {
  Trie trie;

  trie.insert("hello");
  trie.insert("world");

  EXPECT_TRUE(trie.find("hello"));
  EXPECT_TRUE(trie.find("world"));
  EXPECT_FALSE(trie.find("hello world"));
}

TEST(TrieTestFind, insertSamePrefix) {
  Trie trie;

  trie.insert("hello");
  trie.insert("helium");

  EXPECT_TRUE(trie.find("hello"));
  EXPECT_TRUE(trie.find("helium"));
}

TEST(TrieTestStrings, stringsInEmptyTrie) {
  Trie trie;

  ASSERT_EQ(trie.stringsWithPrefix(std::string("hel")),
            std::set<std::string>());
}

TEST(TrieTestStrings, oneStringWithPrefix) {
  Trie trie;

  trie.insert("hello");

  ASSERT_EQ(trie.stringsWithPrefix(std::string("hel")).size(), 1);
}

TEST(TrieTestStrings, multipleStringsSamePrefix) {
  Trie trie;

  trie.insert("hello");
  trie.insert("helium");
  trie.insert("help");

  ASSERT_EQ(trie.stringsWithPrefix(std::string("hel")).size(), 3);
}

TEST(SpellChecker, emptyStrings) {
  Spellchecker sc;
  ASSERT_EQ(0, sc.getEditDistance("", ""));
  EXPECT_EQ(5, sc.getEditDistance("", "hello"));
  EXPECT_EQ(5, sc.getEditDistance("hello", ""));
}

TEST(SpellChecker, equalStrings) {
  Spellchecker sc;
  ASSERT_EQ(0, sc.getEditDistance("hello", "hello"));
}

TEST(SpellChecker, unequalStrings) {
  Spellchecker sc;
  EXPECT_EQ(3, sc.getEditDistance("kitten", "sitting"));
  EXPECT_EQ(3, sc.getEditDistance("saturday", "sunday"));
  EXPECT_EQ(10, sc.getEditDistance("Levenshtein", "distance"));
}

TEST(SpellChecker, longStrings) {
  Spellchecker sc;
  EXPECT_EQ(
      14, sc.getEditDistance("thisisalongteststringtotesteditdistance",
                             "thisisanotherlongstringtotesteditdistanceagain"));
}

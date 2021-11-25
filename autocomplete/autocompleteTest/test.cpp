#include <Autocompleter.h>
#include <Trie.h>

#include <set>
#include <string>
#include <vector>

#include "gtest/gtest.h"
TEST(Autocomplete, emptyString) {
  Autocompleter ac;
  auto strings = ac.getAllStringsFor("");
  std::vector<std::string> emptyList;
  ASSERT_EQ(strings, emptyList);
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

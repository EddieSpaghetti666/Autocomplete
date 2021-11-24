#include <Autocompleter.h>
#include <Trie.h>

#include <string>
#include <vector>

#include "gtest/gtest.h"
TEST(Autocomplete, emptyString) {
  Autocompleter ac;
  auto strings = ac.getAllStringsFor("");
  std::vector<std::string> emptyList;
  ASSERT_EQ(strings, emptyList);
}

TEST(TrieTest, findEmptyString) {
  Trie trie;

  ASSERT_TRUE(trie.find(""));
}
TEST(TrieTest, simpleInsert) {
  Trie trie;

  trie.insert("a");

  ASSERT_TRUE(trie.find("a"));
}

TEST(TrieTest, shouldNotFind) {
  Trie trie;

  trie.insert("hello");

  ASSERT_FALSE(trie.find("world"));
}

TEST(TrieTest, emptyInsert) {
  Trie trie;

  trie.insert("");

  ASSERT_TRUE(trie.find(""));
}

TEST(TrieTest, longerInsert) {
  Trie trie;

  trie.insert("hello");

  ASSERT_TRUE(trie.find("hello"));
}

TEST(TrieTest, multipleInserts) {
  Trie trie;

  trie.insert("hello");
  trie.insert("world");

  EXPECT_TRUE(trie.find("hello"));
  EXPECT_TRUE(trie.find("world"));
  EXPECT_FALSE(trie.find("hello world"));
}

TEST(TrieTest, insertSamePrefix) {
  Trie trie;

  trie.insert("hello");
  trie.insert("helium");

  EXPECT_TRUE(trie.find("hello"));
  EXPECT_TRUE(trie.find("helium"));
}

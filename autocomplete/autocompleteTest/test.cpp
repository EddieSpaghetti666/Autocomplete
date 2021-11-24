#include "gtest/gtest.h"
#include <Autocompleter.h>
#include <vector>
#include <string>
#include <Trie.h>
TEST(Autocomplete, emptyString) {
  Autocompleter ac;
  auto strings = ac.getAllStringsFor("");
  std::vector<std::string> emptyList;
  ASSERT_EQ(strings, emptyList);
}

TEST(TrieTest, insert) {
  Trie trie;

  trie.insert('a');
  
  ASSERT_EQ(trie.leafNodeCount(), 1);

}

#pragma once
#include <string>
#include <vector>

#include "Trie.h"

class Autocompleter {
 public:
  Autocompleter() {};
  Autocompleter(const std::vector<std::string>& dictionary);
  void setDictionary(const std::vector<std::string>& dictionary);
  std::vector<std::string> getAllStringsFor(std::string& prefix) const;

 private:
  void addDictionaryToTrie(const std::vector<std::string>& dictionary);
  Trie trie;
};

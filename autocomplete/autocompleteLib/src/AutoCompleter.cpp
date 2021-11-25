#include "Autocompleter.h"

Autocompleter::Autocompleter(const std::vector<std::string>& dictionary) {
  addDictionaryToTrie(dictionary);
}

void Autocompleter::setDictionary(const std::vector<std::string>& dictionary) {
  addDictionaryToTrie(dictionary);
}

std::vector<std::string> Autocompleter::getAllStringsFor(
    std::string& prefix) const {
  const auto strings = trie.stringsWithPrefix(prefix);
  return std::vector<std::string>(strings.begin(), strings.end());
}

void Autocompleter::addDictionaryToTrie(
    const std::vector<std::string>& dictionary) {
  for (const auto& word : dictionary) {
    trie.insert(word);
  }
}

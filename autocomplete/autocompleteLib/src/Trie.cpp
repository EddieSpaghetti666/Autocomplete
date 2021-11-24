#include "Trie.h"

#include <algorithm>

void Trie::insert(const std::string& key) {
  Node* start = *head;
  for (const char c : key) {
    if (start->children[c] == nullptr) {
      // append new nodes for part of string that isn't already in the trie.
      start->children[c] = new Node();
    }
    start = start->children[c];
  }
}

bool Trie::find(const std::string& key) const {
  Node* start = *head;
  for (const char c : key) {
    if (start->children[c]) {
      start = start->children[c];
    } else
      return false;
  }
  return true;
}

#include "Trie.h"

#include <algorithm>

void Trie::insert(const std::string& key) {
  Node* start = *head;
  for (auto c = key.cbegin(); c != key.cend(); ++c) {
    if (start->children[*c] == nullptr) {
      // append new nodes for part of string that isn't already in the trie.
      start->children[*c] = new Node(*c);
    }
    start = start->children[*c];
  }
  start->isEnd = true;
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

std::set<std::string> Trie::stringsWithPrefix(std::string& prefix) const {
  std::set<std::string> strings;
  auto node = getNode(prefix);
  collectStrings(node, prefix, strings);
  return strings;
}

Trie::Node* Trie::getNode(const std::string& prefix) const {
  Node* start = *head;
  for (const char c : prefix) {
    if (start->children[c]) {
      start = start->children[c];
    } else
      return nullptr;
  }
  return start;
}

void Trie::collectStrings(Node* node, std::string& prefix,
                          std::set<std::string>& strings) const {
  if (node == nullptr) return;
  if (node->isEnd) 
      strings.insert(prefix);
  for (auto child : node->children) {
    if (child != nullptr) {
      char c = child->c;
      prefix += c;
      collectStrings(node->children[c], prefix, strings);
      prefix.pop_back();
    }
  }
}

#pragma once
#include <string>
#include <vector>
class Trie {
  struct Node {
    Node* children[255];
  };

 public:
  Trie() : head(new Node*(new Node())) {}

  void insert(const std::string& key);

  bool find(const std::string& key) const;

 private:
  Node** head;
};

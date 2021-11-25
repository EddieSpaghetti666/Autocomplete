#pragma once
#include <set>
#include <string>
#include <vector>
class Trie {
  struct Node {
    Node(char c, bool isEnd = false) : c(c), isEnd(isEnd), children() {}
    bool isEnd;
    char c;
    Node* children[255];
  };

 public:
  Trie() : head(new Node*(new Node('\0'))) {}

  void insert(const std::string& key);

  bool find(const std::string& key) const;

  std::set<std::string> stringsWithPrefix(std::string& prefix) const;

 private:
  Node** head;

  Node* getNode(const std::string& prefix) const;

  void collectStrings(Node* node, std::string& prefix,
                      std::set<std::string>& strings) const;
};

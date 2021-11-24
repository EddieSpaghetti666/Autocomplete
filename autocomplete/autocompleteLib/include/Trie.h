#pragma once
#include <vector>
class Trie {
  struct Node {
    std::vector<Node*> children;
  };

 public:
  void insert(char c);
  uint32_t leafNodeCount() const; 
 private:
  Node* head;
};

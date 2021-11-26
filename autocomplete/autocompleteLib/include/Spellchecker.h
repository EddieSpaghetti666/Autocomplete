#pragma once
#include <string>
class Spellchecker {
 public:
  int getEditDistance(const std::string& word1, const std::string& word2);
};

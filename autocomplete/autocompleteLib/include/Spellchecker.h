#pragma once
#include <string>
#include <vector>
class Spellchecker {
 public:
  Spellchecker(const std::vector<std::string>& dictionary,
               const size_t editDistance)
      : dictionary(dictionary), maxEditDistance(editDistance){};

  Spellchecker() : dictionary(std::vector<std::string>()), maxEditDistance(0){};

  size_t getEditDistance(const std::string& word1, const std::string& word2);

  void setDictionary(const std::vector<std::string>& dictionary) {
    this->dictionary = dictionary;
  }

  void setMaxEditDistance(const size_t distance) {
    this->maxEditDistance = distance;
  }

	std::vector<std::string> closestWords(const std::string& word);

	std::vector<std::string> withCloseEnoughPrefix(const std::string& word);

 private:
  std::vector<std::string> dictionary;
  size_t maxEditDistance;
};

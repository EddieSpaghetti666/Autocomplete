#include <Autocompleter.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> loadDictionary(std::string fileName) {
  std::fstream fs(fileName);
  std::vector<std::string> dictionary;
  std::string word;
  while (fs >> word) {
    std::transform(word.begin(), word.end(), word.begin(), std::tolower);
    dictionary.push_back(word);
  }
  return dictionary;
}
int main() {
  const auto dictionary = loadDictionary("fruits.txt");
  Autocompleter ac(dictionary);
  while (true) {
    std::string prefix;
    std::cout << "Please enter a prefix you want autocompleted:\n"
              << std::endl;
    std::cin >> prefix;
    const auto words = ac.getAllStringsFor(prefix);
    for (const auto& word : words) {
      std::cout << word << std::endl;
    }
  }
  return 0;
}

#include "Spellchecker.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<std::vector<int>> createInitialMatrix(const size_t word1Size,
                                                  const size_t word2Size) {
  std::vector<std::vector<int>> matrix(word2Size + 1,
                                       std::vector<int>(word1Size + 1, 0));
  std::iota(matrix[0].begin() + 1, matrix[0].end(), 1);
  for (size_t j = 1; j < word2Size + 1; ++j) {
    matrix[j][0] = j;
  }
  return matrix;
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
  for (auto row : matrix) {
    for (int num : row) {
      std::cout << num << " ";
    }
    std::cout << "\n" << std::endl;
  }
}

size_t Spellchecker::getEditDistance(const std::string& word1,
                                     const std::string& word2) {
  if (word1.empty() && word2.empty())
    return 0;
  else if (word1.empty())
    return word2.size();
  else if (word2.empty())
    return word1.size();

  auto matrix = createInitialMatrix(word1.size(), word2.size());

  for (size_t i = 1; i < word2.size() + 1; ++i) {
    for (size_t j = 1; j < word1.size() + 1; ++j) {
      int substitutionCost = 0;
      if (word1[j - 1] != word2[i - 1]) substitutionCost = 1;
      const int deletion = matrix[i - 1][j] + 1;
      const int insertion = matrix[i][j - 1] + 1;
      const int substitution = matrix[i - 1][j - 1] + substitutionCost;
      matrix[i][j] = std::min({deletion, insertion, substitution});
    }
  }
  return matrix[word2.size()][word1.size()];
}

std::vector<std::string> Spellchecker::closestWords(const std::string& word) {
  std::vector<std::string> closestWords;

  auto withinEditDistance = [=](const std::string& word2) -> bool {
    return getEditDistance(word, word2) <= maxEditDistance;
  };

  std::copy_if(dictionary.begin(), dictionary.end(),
               std::back_inserter(closestWords), withinEditDistance);

  return closestWords;
}

std::vector<std::string> Spellchecker::withCloseEnoughPrefix(
    const std::string& word) {
  const size_t length = word.size();
  std::string test("Apricot", 0, length);
  auto withinEditDistance = [=](const std::string& word2) -> bool {
    return getEditDistance(word, std::string(word2, 0, length)) <=
           maxEditDistance;
  };

  std::vector<std::string> closeEnough;

  std::copy_if(dictionary.begin(), dictionary.end(),
               std::back_inserter(closeEnough), withinEditDistance);

  return closeEnough;
}

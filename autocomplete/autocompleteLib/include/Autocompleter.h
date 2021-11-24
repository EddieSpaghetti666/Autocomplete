#pragma once
#include <string>
#include <vector>
class Autocompleter {
 public:
  std::vector<std::string> getAllStringsFor(const std::string& prefix) const;
};

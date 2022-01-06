#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

std::unordered_map<std::string, long> pairFrequency;
std::unordered_map<std::string, std::pair<std::string, std::string>>
    pairEvolution;
std::unordered_map<char, long> elementFrequency;

void print_counts() {
  long max = INT64_MIN, min = INT64_MAX, n = 0;
  auto it = elementFrequency.begin();
  while (it != elementFrequency.end()) {
    std::cout << it->first << " " << it->second << std::endl;
    n += it->second;
    max = std::max(max, it->second);
    min = std::min(min, it->second);
    it++;
  }
  std::cout << n << " " << min << " " << max << " " << max - min << " "
            << std::endl;
}

int main() {

  std::string line;

  std::cin >> line;

  for (int i = 0; i < line.size() - 1; i++) {
    pairFrequency[line.substr(i, 2)]++;
    elementFrequency[line[i]]++;
  }
  elementFrequency[line[line.size() - 1]]++;

  while (std::cin >> line) {
    std::string line2;
    std::cin >> line2;
    std::cin >> line2;

    std::string line1Copy(line);
    line1Copy.insert(line1Copy.begin() + 1, line2[0]);
    pairEvolution[line] =
        std::make_pair(line1Copy.substr(0, 2), line1Copy.substr(1, 2));
  }

  for (int i = 0; i < 40; i++) {
    auto frequencyCopy = std::move(pairFrequency);
    pairFrequency.clear();
    auto it = frequencyCopy.begin();
    while (it != frequencyCopy.end()) {
      pairFrequency[pairEvolution[it->first].first] += it->second;
      pairFrequency[pairEvolution[it->first].second] += it->second;
      elementFrequency[pairEvolution[it->first].first[1]] += it->second;
      it++;
    }
  }
  print_counts();

  return 0;
}
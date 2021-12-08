#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#define DIV_ROUND_CLOSEST(n, d)                                                \
  ((((n) < 0) ^ ((d) < 0)) ? (((n) - (d) / 2) / (d)) : (((n) + (d) / 2) / (d)))

int main() {
  std::vector<int> nums;

  std::string line;
  std::cin >> line;
  std::stringstream ss(line);
  int num, sum = 0;
  while (ss >> num) {
    sum += num;
    nums.push_back(num);
    if (ss.peek() == ',') {
      ss.ignore();
    }
  }

  std::vector<int> candidates;

  int avg = sum / nums.size();
  candidates.push_back(avg);
  if (avg * nums.size() != sum)
    candidates.push_back(avg + 1);

  int fuel = INT32_MAX;
  for (int c : candidates) {
    int result = std::transform_reduce(
        nums.begin(), nums.end(), 0, std::plus<>(),
        [c](int n) { return std::abs(n - c) * (std::abs(n - c) + 1) / 2; });
    fuel = std::min(result, fuel);
  }

  std::cout << fuel << std::endl;

  return 0;
}
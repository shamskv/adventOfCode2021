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

  int avg = sum / nums.size();
  std::cout << sum << std::endl;
  std::cout << nums.size() << std::endl;
  std::cout << avg << std::endl;

  int result = std::transform_reduce(
      nums.begin(), nums.end(), 0, std::plus<>(),
      [avg](int n) { return std::abs(n - avg) * (std::abs(n - avg) + 1) / 2; });

  std::cout << result << std::endl;

  return 0;
}
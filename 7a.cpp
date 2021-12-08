#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::vector<int> nums;

  std::string line;
  std::cin >> line;
  std::stringstream ss(line);
  int num, sum = 0;
  while (ss >> num) {
    nums.push_back(num);
    if (ss.peek() == ',') {
      ss.ignore();
    }
  }
  std::sort(nums.begin(), nums.end());

  std::vector<int> candidates;

  candidates.push_back(nums[nums.size() / 2]);
  if (nums.size() % 2 == 0)
    candidates.push_back(nums[(nums.size() / 2) - 1]);

  int fuel = INT32_MAX;
  for (int c : candidates) {
    int result =
        std::transform_reduce(nums.begin(), nums.end(), 0, std::plus<>(),
                              [c](int n) { return std::abs(n - c); });
    fuel = std::min(result, fuel);
  }

  std::cout << fuel << std::endl;

  return 0;
}
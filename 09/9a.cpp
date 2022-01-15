#include <iostream>
#include <string>
#include <vector>

template <typename T> void vec_set(const std::vector<T> &vec, const T &value) {
  for (T &it : vec) {
    it = value;
  }
}

int main() {
  int row_length, sum = 0;
  std::vector<int> prev_num, curr_num;
  std::vector<bool> prev_bool, curr_bool;

  std::string line;
  std::cin >> line;
  row_length = line.size();

  prev_num = std::vector<int>(row_length, 10);
  curr_num = std::vector<int>(row_length, 0);

  prev_bool = std::vector<bool>(row_length, false);
  curr_bool = std::vector<bool>(row_length, true);

  do {
    // Set curr line
    for (int i = 0; i < row_length; i++) {
      curr_num[i] = line[i] - '0';
      curr_bool[i] = true;
    }
    // Comparisons
    for (int i = 0; i < row_length; i++) {
      // Vertical comparison
      if (curr_num[i] < prev_num[i]) {
        prev_bool[i] = false;
      } else if (curr_num[i] > prev_num[i]) {
        curr_bool[i] = false;
      } else {
        prev_bool[i] = false;
        curr_bool[i] = false;
      }
      // Horizontal comparison
      if (i > 0 && curr_num[i] >= curr_num[i - 1]) {
        curr_bool[i] = false;
      }
      if (i < row_length - 1 && curr_num[i] >= curr_num[i + 1]) {
        curr_bool[i] = false;
      }
    }
    // Get low points
    for (int i = 0; i < row_length; i++) {
      if (prev_bool[i]) {
        sum += prev_num[i] + 1;
      }
    }
    // Move curr to prev
    for (int i = 0; i < row_length; i++) {
      prev_num[i] = curr_num[i];
      prev_bool[i] = curr_bool[i];
    }
  } while (std::cin >> line);

  // Low points for last row
  for (int i = 0; i < row_length; i++) {
    if (prev_bool[i]) {
      sum += prev_num[i] + 1;
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
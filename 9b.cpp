#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

template <typename T> void vec_set(const std::vector<T> &vec, const T &value) {
  for (T &it : vec) {
    it = value;
  }
}

int calculate_basin(const std::vector<std::vector<int>> &matrix,
                    std::vector<std::vector<int>> &visited, int m, int n) {
  // printf("basin %d %d\n", m, n);
  if (m < 0 || m >= matrix.size()) {
    return 0;
  }
  if (n < 0 || n >= matrix.front().size()) {
    return 0;
  }

  if (visited[m][n]++) {
    return 0;
  }

  if (matrix[m][n] == 9) {
    return 0;
  }

  return 1 + calculate_basin(matrix, visited, m + 1, n) +
         calculate_basin(matrix, visited, m - 1, n) +
         calculate_basin(matrix, visited, m, n + 1) +
         calculate_basin(matrix, visited, m, n - 1);
}

typedef std::pair<int, int> coordinates;

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

  int n_line = -1;
  std::vector<coordinates> low_points;
  std::vector<std::vector<int>> matrix;

  do {
    // Set curr line
    std::vector<int> line_vec;
    for (int i = 0; i < row_length; i++) {
      curr_num[i] = line[i] - '0';
      curr_bool[i] = true;
      line_vec.push_back(curr_num[i]);
    }
    matrix.push_back(std::move(line_vec));
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
        low_points.emplace_back(n_line, i);
      }
    }
    // Move curr to prev
    for (int i = 0; i < row_length; i++) {
      prev_num[i] = curr_num[i];
      prev_bool[i] = curr_bool[i];
    }
    n_line++;
  } while (std::cin >> line);

  // Low points for last row
  for (int i = 0; i < row_length; i++) {
    if (prev_bool[i]) {
      sum += prev_num[i] + 1;
      low_points.emplace_back(n_line, i);
    }
  }

  std::cout << sum << std::endl;

  // Calculate basin for each low point
  std::multiset<int> results;
  std::vector<std::vector<int>> visited;
  for (int i = 0; i <= n_line; i++) {
    visited.emplace_back(row_length, 0);
  }
  printf("matrix %d %d\n", matrix.size(), matrix.front().size());

  for (auto &low_point : low_points) {
    printf("low point %d %d\n", low_point.first, low_point.second);
    if (!visited[low_point.first][low_point.second]) {
      int r =
          calculate_basin(matrix, visited, low_point.first, low_point.second);
      printf("result %d\n", r);
      results.emplace(r);
    }
  }

  int mult = 1;
  auto it = results.rbegin();
  for (int i = 0; i < 3; i++) {
    mult *= *it++;
  }

  std::cout << mult << std::endl;

  return 0;
}
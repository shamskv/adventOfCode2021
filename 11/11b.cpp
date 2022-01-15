#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

void printm(std::vector<std::vector<int>> &matrix) {
  printf("\n");

  for (auto &m : matrix) {
    for (auto &i : m) {
      printf("%d ", i);
    }
    printf("\n");
  }
}

int advance(std::vector<std::vector<int>> &matrix) {
  int explosions = 0;
  int n = matrix.size(); // assume it's always a square

  std::stack<std::pair<int, int>> bump_pool;

  // All positions get bumped once
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      bump_pool.push(std::make_pair(i, j));
  }

  // Main loop
  while (!bump_pool.empty()) {
    auto pos = bump_pool.top();
    bump_pool.pop();
    int x = pos.first, y = pos.second;
    if (x < 0 || x >= n || y < 0 || y >= n || matrix[x][y] == -1) {
      continue;
    }
    if (++matrix[x][y] > 9) {
      explosions++;
      matrix[x][y] = -1;
      bump_pool.push(std::make_pair(x + 1, y - 1));
      bump_pool.push(std::make_pair(x + 1, y));
      bump_pool.push(std::make_pair(x + 1, y + 1));
      bump_pool.push(std::make_pair(x, y - 1));
      bump_pool.push(std::make_pair(x, y + 1));
      bump_pool.push(std::make_pair(x - 1, y - 1));
      bump_pool.push(std::make_pair(x - 1, y));
      bump_pool.push(std::make_pair(x - 1, y + 1));
    }
  }

  // Explodeds are 0 now
  for (auto &m : matrix) {
    for (auto &i : m) {
      if (i == -1)
        i = 0;
    }
  }

  return explosions;
}

int main() {

  std::string line;
  std::vector<std::vector<int>> matrix;

  while (std::cin >> line) {
    matrix.emplace_back();
    for (char c : line) {
      matrix.back().push_back(c - '0');
    }
  }

  int iter = 0;
  while (true) {
    iter++;
    if (advance(matrix) == matrix.size() * matrix.size()) {
      break;
    }
  }

  std::cout << iter << std::endl;
  return 0;
}
#include <iostream>
#include <sstream>
#include <string>

#define GRID_SIZE 1000

int main() {
  std::string line;
  int grid[GRID_SIZE][GRID_SIZE] = {0};

  while (std::cin.peek() != EOF) {
    int x1, x2, y1, y2;
    std::cin >> line;
    std::stringstream ss(line);
    ss >> x1;
    ss.ignore();
    ss >> y1;
    std::cin >> line;
    std::cin >> line;
    std::stringstream ss2(line);
    ss2 >> x2;
    ss2.ignore();
    ss2 >> y2;

    int delta_x = x2 - x1, delta_y = y2 - y1;
    int tendency_x, tendency_y, iters;

    iters = delta_x != 0 ? std::abs(delta_x) : std::abs(delta_y);
    tendency_x = delta_x / iters;
    tendency_y = delta_y / iters;

    for (int i = 0; i <= iters; i++) {
      grid[x1][y1]++;
      x1 += tendency_x;
      y1 += tendency_y;
    }
  }

  int sum = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (grid[i][j] > 1)
        sum++;
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
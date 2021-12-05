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

    // printf(" %d %d -> %d %d\n", x1, y1, x2, y2);
    if (x1 != x2 && y1 != y2) {
      continue;
    }

    if (x1 > x2)
      std::swap(x1, x2);
    else if (y1 > y2)
      std::swap(y1, y2);

    for (int i = x1; i <= x2; i++) {
      for (int j = y1; j <= y2; j++) {
        grid[i][j]++;
      }
    }
  }

  int sum = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      // printf("%d ", grid[i][j]);
      if (grid[i][j] > 1)
        sum++;
    }
    // printf("\n");
  }

  std::cout << sum << std::endl;

  return 0;
}
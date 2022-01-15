#include <iostream>
#include <string>
#include <vector>

#define M_SIZE 2000

std::vector<std::vector<bool>>
    matrix(M_SIZE, std::vector<bool>(M_SIZE, false)); // DATA LOCALITY KEKW
int x_max = M_SIZE, y_max = M_SIZE;

int main() {

  std::string line;

  while (std::cin >> line) {
    int x, y;
    if (line[0] == 'f')
      break;
    sscanf(line.c_str(), "%d,%d", &x, &y);
    matrix[x][y] = true;
  }

  do {
    char direction;
    int middle;
    if (sscanf(line.c_str(), "%c=%d", &direction, &middle) != 2) {
      continue;
    }
    printf("folding %c at %d\n", direction, middle);
    if (direction == 'x') {
      for (int x = 0; x < middle; x++) {
        for (int y = 0; y < y_max; y++) {
          matrix[x][y] = matrix[x][y] | matrix[2 * middle - x][y];
        }
      }
      x_max = middle;
    } else if (direction == 'y') {
      for (int x = 0; x < x_max; x++) {
        for (int y = 0; y < middle; y++) {
          matrix[x][y] = matrix[x][y] | matrix[x][2 * middle - y];
        }
      }
      y_max = middle;
    }
  } while (std::cin >> line);

  int sum = 0;
  for (int y = 0; y < y_max; y++) {
    for (int x = 0; x < x_max; x++) {
      printf("%c", matrix[x][y] ? '#' : '.');
      sum += matrix[x][y];
    }
    printf("\n");
  }

  std::cout << sum << std::endl;
}
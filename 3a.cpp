#include <iostream>
#include <math.h>
#include <string>

#define NBITS 12

int main() {
  int pos[NBITS] = {0};
  int n_rows = 0, gamma = 0;
  std::string row;

  while (std::cin >> row) {
    for (int i = 0; i < NBITS; i++) {
      pos[i] += row[NBITS - 1 - i] - 48;
    }
    n_rows++;
  }

  for (int i = 0; i < NBITS; i++) {
    if (n_rows / 2 < pos[i]) {
      gamma += (1 << i);
    }
  }

  std::cout << gamma * (gamma ^ 0b111111111111) << std::endl;

  return 0;
}
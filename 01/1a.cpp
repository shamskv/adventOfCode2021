#include <fstream>
#include <iostream>

int main() {
  std::ifstream input;
  input.open("1.in");

  int prev, next, sum = 0;

  input >> prev;

  while (input >> next) {
    if (next > prev) {
      sum++;
    }
    prev = next;
  }

  std::cout << sum << std::endl;

  return 0;
}
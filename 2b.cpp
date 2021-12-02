#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream input;
  input.open("2.in");

  int horizontal = 0, depth = 0, aim = 0;

  std::string inst;
  int value;

  while (input >> inst >> value) {
    if (inst.size() == 2) {
      aim -= value;
    } else if (inst.size() == 4) {
      aim += value;
    } else {
      horizontal += value;
      depth += aim * value;
    }
  }

  std::cout << horizontal * depth << std::endl;
  return 0;
}
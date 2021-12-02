#include <deque>
#include <fstream>
#include <iostream>

int main() {
  std::ifstream input;
  input.open("1.in");

  int temp, prev, next, sum = 0;

  std::deque<int> sliding;

  for (int i = 0; i < 3 && input >> temp; i++) {
    sliding.push_back(temp);
    prev += temp;
  }

  while (input >> temp) {
    next = prev + temp - sliding.front();
    if (next > prev) {
      sum++;
    }

    sliding.pop_front();
    sliding.push_back(temp);
    prev = next;
  }

  std::cout << sum << std::endl;

  return 0;
}
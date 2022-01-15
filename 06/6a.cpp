#include <iostream>
#include <sstream>
#include <string>

#define PERIOD 8
#define DAY 80
#define TARGET_DAY DAY + PERIOD

int main() {

  int score[TARGET_DAY] = {0};

  for (int d = TARGET_DAY - 1; d >= 0; d--) {
    score[d] = 1;
    for (int c = d + 9; c < TARGET_DAY; c += 7) {
      score[d] += score[c];
    }
  }

  //   for (int i = 0; i < TARGET_DAY; i++) {
  //     printf("day %d score %d\n", i - PERIOD + 1, score[i]);
  //   }

  std::string line;
  std::cin >> line;
  std::stringstream ss(line);
  int num, sum = 0;
  while (ss >> num) {
    sum += score[num - 1];
    if (ss.peek() == ',') {
      ss.ignore();
    }
  }

  printf("%d\n", sum);

  return 0;
}
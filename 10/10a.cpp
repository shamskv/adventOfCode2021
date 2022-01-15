#include <iostream>
#include <map>
#include <stack>
#include <string>

std::map<char, int> scoreMap = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
std::map<char, char> openMap = {{')', '('}, {']', '['}, {'}', '{'}, {'>', '<'}};

int main() {
  std::string line;
  int score = 0;

  while (std::cin >> line) {
    std::stack<char> openStack;
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ')' || line[i] == ']' || line[i] == '}' ||
          line[i] == '>') {
        if (openStack.top() != openMap[line[i]]) {
          printf("Invalid %c i=%d \n", line[i], i);
          score += scoreMap[line[i]];
          break;
        } else {
          openStack.pop();
        }
      } else {
        openStack.push(line[i]);
      }
    }
  }

  std::cout << score << std::endl;

  return 0;
}
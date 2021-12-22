#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

std::map<char, int> scoreMap = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
std::map<char, char> openMap = {{')', '('}, {']', '['}, {'}', '{'}, {'>', '<'}};

int main() {
  std::string line;
  std::vector<int> scores;

  while (std::cin >> line) {
    std::stack<char> openStack;
    bool valid = true;
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ')' || line[i] == ']' || line[i] == '}' ||
          line[i] == '>') {
        if (openStack.top() != openMap[line[i]]) {
          valid = false;
          break;
        } else {
          openStack.pop();
        }
      } else {
        openStack.push(line[i]);
      }
    }
    if (valid) {
      int line_score = 0;
      while (!openStack.empty()) {
        line_score *= 5;
        line_score += scoreMap[openStack.top()];
        openStack.pop();
      }
      scores.push_back(line_score);
    }
  }

  for (auto &score : scores) {
    printf("%d\n", score);
  }

  return 0;
}
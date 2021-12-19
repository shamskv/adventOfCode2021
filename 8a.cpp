#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Problem {
public:
  vector<string> input;
  vector<string> output;
};

int main() {
  vector<Problem> problems;

  for (string line; getline(cin, line);) {
    stringstream ss(line);
    std::string code;
    problems.emplace_back();
    while (ss >> code) {
      if (code == "|")
        break;
      problems.back().input.push_back(code);
    }
    while (ss >> code) {
      problems.back().output.push_back(code);
    }
  }

  int sum = 0;
  for (auto &p : problems) {
    for (auto &c : p.output) {
      if (c.size() == 2 || c.size() == 3 || c.size() == 4 || c.size() == 7)
        sum++;
    }
  }

  cout << sum << endl;

  return 0;
}
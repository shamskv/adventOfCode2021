#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::vector<std::string>> paths;

bool isLowerCase(std::string &str) {
  return std::all_of(str.begin(), str.end(),
                     [](unsigned char c) { return std::islower(c); });
}

int main() {
  std::string line;
  std::unordered_map<std::string, std::vector<std::string>> edges;

  while (std::cin >> line) {
    int pos = line.find("-");
    std::string from = line.substr(0, pos);
    std::string to = line.substr(pos + 1);
    edges[from].push_back(to);
    edges[to].push_back(from);
  }

  std::stack<std::string> stek;
  stek.push("start");
  std::vector<std::string> currPath;
  while (!stek.empty()) {
    auto currNode = stek.top();
    stek.pop();
    // if small node, check if we are not in path already
    if (isLowerCase(currNode)) {
      if (std::find(currPath.begin(), currPath.end(), currNode) !=
          currPath.end()) {
        continue;
      }
    }
    currPath.push_back(currNode);
    // if end we end path here
    if (currNode == "end") {
      paths.push_back(currPath);
      currPath.pop_back();
      continue;
    }
  }

  return 0;
}
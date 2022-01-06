#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

std::vector<std::vector<std::string>> paths;
bool exception_allowed = true;

bool isLowerCase(std::string &str) {
  return std::all_of(str.begin(), str.end(),
                     [](unsigned char c) { return std::islower(c); });
}

void printPath(std::vector<std::string> &path) {
  for (auto &node : path) {
    std::cout << node << " ";
  }
  std::cout << std::endl;
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

  std::stack<std::pair<std::string, bool>> stek;
  stek.emplace("start", true);
  std::vector<std::string> currPath;
  while (!stek.empty()) {
    auto currNode = stek.top().first;
    bool backtrack = !stek.top().second;
    stek.pop();
    // Backtrack if we are on our way "back"
    if (backtrack) {
      currPath.pop_back();
      // If I'm still in path after leaving, I was using the exception
      if (isLowerCase(currNode)) {
        if (std::find(currPath.begin(), currPath.end(), currNode) !=
            currPath.end()) {
          exception_allowed = true;
        }
      }
      continue;
    }
    // if small node, check if we are not in path already
    if (isLowerCase(currNode)) {
      if (std::find(currPath.begin(), currPath.end(), currNode) !=
          currPath.end()) {
        if (!exception_allowed || currNode == "start") {
          continue;
        } else {
          exception_allowed = false;
        }
      }
    }
    // Place current node on current path and add backtrack entry to stack
    currPath.push_back(currNode);
    stek.emplace(currNode, false);
    // if end we end path here
    if (currNode == "end") {
      paths.push_back(currPath);
      continue;
    }
    // Place childs in stack
    for (auto &child : edges[currNode]) {
      stek.emplace(child, true);
    }
  }

  std::cout << paths.size() << std::endl;

  return 0;
}
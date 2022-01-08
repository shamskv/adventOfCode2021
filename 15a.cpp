#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class Matrix {
 private:
  std::vector<T> matrix;
  int x_s, y_s;

 public:
  Matrix(int x_size, int y_size)
      : x_s(x_size), y_s(y_size), matrix(x_size * y_size) {}

  T &operator()(int x, int y) { return matrix.at(x * x_s + y); }
  T &operator()(const std::pair<int, int> &xy) {
    return matrix.at(xy.first * x_s + xy.second);
  }
};

typedef std::pair<long, std::pair<int, int>> weightedNode;

int main() {
  std::string line;

  std::cin >> line;
  int matrixLength = line.size();
  Matrix<int> matrix(matrixLength, matrixLength);
  Matrix<int> visitedMatrix(
      matrixLength, matrixLength);  // not using bool cuz specializations dont
                                    // allow the () operator to work well

  int y = 0;
  do {
    for (int x = 0; x < matrixLength; x++) {
      matrix(x, y) = line[x] - '0';
      visitedMatrix(x, y) = 0;
    }
    y++;
  } while (std::cin >> line);

  std::priority_queue<weightedNode, std::vector<weightedNode>,
                      std::greater<weightedNode>>
      heap;
  heap.emplace(0, std::make_pair(0, 0));

  while (!heap.empty()) {
    auto curr = heap.top();
    auto &pos = curr.second;
    auto &weight = curr.first;
    heap.pop();

    int &visited = visitedMatrix(pos.first, pos.second);
    if (visited) {
      continue;
    } else {
      visited = 1;
    }

    if (pos.first == matrixLength - 1 && pos.second == matrixLength - 1) {
      std::cout << weight << std::endl;
      break;
    }

    // Create neighbors
    auto newPos = std::make_pair(pos.first - 1, pos.second);
    if (newPos.first > 0 && !visitedMatrix(newPos)) {
      heap.emplace(weight + matrix(newPos), newPos);
    }
    newPos = std::make_pair(pos.first + 1, pos.second);
    if (newPos.first < matrixLength && !visitedMatrix(newPos)) {
      heap.emplace(weight + matrix(newPos), newPos);
    }
    newPos = std::make_pair(pos.first, pos.second - 1);
    if (newPos.second > 0 && !visitedMatrix(newPos)) {
      heap.emplace(weight + matrix(newPos), newPos);
    }
    newPos = std::make_pair(pos.first, pos.second + 1);
    if (newPos.second < matrixLength && !visitedMatrix(newPos)) {
      heap.emplace(weight + matrix(newPos), newPos);
    }
  }

  return 0;
}
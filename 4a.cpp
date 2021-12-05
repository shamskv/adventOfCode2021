#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#define BOARD_SIZE 5

typedef std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> board_grid;

class Board {
public:
  std::shared_ptr<board_grid> values;
  std::shared_ptr<board_grid> mark;

  int *valueToMarkPtr[100] = {nullptr};

  Board() {
    mark = std::make_shared<board_grid>();
    values = std::make_shared<board_grid>();
  }

  bool isComplete() {
    for (int i = 0; i < BOARD_SIZE; i++) {
      // column i
      bool all_marked = true;
      for (int j = 0; j < BOARD_SIZE; j++) {
        all_marked &= (*mark)[i][j];
      }
      if (all_marked) {
        return true;
      }
      // row i
      all_marked = true;
      for (int j = 0; j < BOARD_SIZE; j++) {
        all_marked &= (*mark)[j][i];
      }
      if (all_marked) {
        return true;
      }
    }
    return false;
  }

  void addValue(int i, int j, int value) {
    (*values)[i][j] = value;
    valueToMarkPtr[value] = &(*mark)[i][j];
  }

  bool markValue(int value) {
    int *placeToMark = valueToMarkPtr[value];
    if (placeToMark != nullptr) {
      *placeToMark = 1;
      return true;
    }
    return false;
  }

  void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        printf("%2d ", (*values)[i][j]);
      }
      printf("\t");
      for (int j = 0; j < BOARD_SIZE; j++) {
        printf("%d ", (*mark)[i][j]);
      }
      printf("\n");
    }
    printf("\n");
  }

  int sumOfUnmarked() {
    int sum = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        sum += ((*mark)[i][j] ^ 1) * (*values)[i][j];
      }
    }
    return sum;
  }
};

int main() {
  std::vector<Board> boardList;
  std::vector<int> drawValues;
  std::string line;

  // Parse first line
  std::cin >> line;
  std::stringstream ss(line);
  for (int i; ss >> i;) {
    drawValues.push_back(i);
    if (ss.peek() == ',') {
      ss.ignore();
    }
  }

  // parse the numbers idk how this works
  while (std::cin.peek() != EOF) {
    Board curr_board;
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        int n;
        std::cin >> n;
        curr_board.addValue(i, j, n);
      }
    }
    boardList.push_back(curr_board);
  }

  for (int nextValue : drawValues) {
    for (Board &b : boardList) {
      if (b.markValue(nextValue) && b.isComplete()) {
        std::cout << b.sumOfUnmarked() * nextValue << std::endl;
        b.printBoard();
        return 0;
      }
    }
  }

  return 0;
}
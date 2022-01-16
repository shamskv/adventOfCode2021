#include <iostream>
#include <string>
#include <vector>

class Matrix {
 public:
  std::vector<std::vector<bool>> matrix;
  int x_size, y_size;
  bool infinite_value;

  Matrix(int x, int y, bool v)
      : x_size(x),
        y_size(y),
        infinite_value(v),
        matrix(x, std::vector<bool>(y, v)) {}

  Matrix(Matrix const& copied)
      : Matrix(copied.x_size, copied.y_size, copied.infinite_value) {
    for (int i = 0; i < x_size; i++) {
      for (int j = 0; j < y_size; j++) {
        this->matrix[i][j] = copied.matrix[i][j];
      }
    }
  }

  // Cant return a reference because of std::vector bool specialization
  bool operator()(int x, int y) {
    if (x < 0 || x >= x_size || y < 0 || y >= y_size) {
      return infinite_value;
    }
    return matrix[x][y];
  }

  void setValue(int x, int y, bool v) { matrix[x][y] = v; }

  // Should just expand on copy constructor automatically to avoid this but w/e
  void expand() {
    x_size += 2;
    y_size += 2;
    for (auto& vec : matrix) {
      vec.insert(vec.begin(), infinite_value);
      vec.insert(vec.end(), infinite_value);
    }
    matrix.insert(matrix.begin(), std::vector<bool>(y_size, infinite_value));
    matrix.insert(matrix.end(), std::vector<bool>(y_size, infinite_value));
  }

  void print(int x1, int x2, int y1, int y2) {
    int counter = 0;
    for (int y = y1; y < y2; y++) {
      for (int x = x1; x < x2; x++) {
        // printf("%c", this->operator()(x, y) ? '#' : '.');
        counter += this->operator()(x, y);
      }
      // printf("\n");
    }
    printf("%d\n", counter);
  }

  void print() { this->print(0, x_size, 0, y_size); }
};

int readSquare(Matrix& m, int x, int y) {
  int shift = 8;
  int out = 0;
  for (int j = y - 1; j <= y + 1; j++) {
    for (int i = x - 1; i <= x + 1; i++) {
      out += m(i, j) << shift--;
    }
  }
  return out;
}

std::vector<bool> algorithm;

int main() {
  std::string line;
  std::cin >> line;
  // Parse input
  algorithm.reserve(line.size());
  for (int i = 0; i < line.size(); i++) {
    algorithm.push_back(line[i] == '#');
  }
  std::cin >> line;
  int j = 0;
  Matrix m(line.size(), line.size(), false);
  do {
    for (int i = 0; i < line.size(); i++) {
      m.setValue(i, j, line[i] == '#');
    }
    j++;
  } while (std::cin >> line);

  std::vector<Matrix> mList;
  mList.push_back(m);
  for (int i = 1; i < 51; i++) {
    mList.emplace_back(mList[i - 1]);
    Matrix& m_in = mList[i - 1];
    Matrix& m_out = mList[i];
    m_out.expand();

    for (int x = 0; x < m_out.x_size; x++) {
      for (int y = 0; y < m_out.y_size; y++) {
        m_out.setValue(x, y, algorithm[readSquare(m_in, x - 1, y - 1)]);
      }
    }

    m_out.infinite_value =
        m_in.infinite_value ? algorithm.back() : algorithm.front();

    m_out.print();
  }
  return 0;
}
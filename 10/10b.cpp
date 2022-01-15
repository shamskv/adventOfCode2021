#include <iostream>
#include <map>
#include <stack>
#include <string>

template <typename T, class Compare> class MyHeap {
private:
  T *t;
  int size, capacity;
  Compare comparator;

  void increase_capacity() {
    int old_capacity = capacity;
    capacity *= 2;
    T *new_ptr = new T[capacity];
    std::uninitialized_copy(t, t + old_capacity, new_ptr);
    delete t;
    t = new_ptr;
  }

public:
  MyHeap() : size(0), capacity(10) { t = new T[capacity]; }
  ~MyHeap() { delete t; }

  const T &getRoot() { return t[1]; }

  T getAndPopRoot() {
    if (size < 1)
      return T();
    T root = t[1];
    t[1] = t[size--]; // also "removes" last element
    for (int pos = 1;;) {
      bool leftSwap = false, rightSwap = false;
      int leftChild = pos * 2, rightChild = (pos * 2) + 1;
      if (leftChild <= size && !comparator(t[pos], t[leftChild])) {
        leftSwap = true;
      }
      if (rightChild <= size && !comparator(t[pos], t[rightChild])) {
        rightSwap = true;
      }
      // Tiebreak if both childs are eligible
      if (leftSwap && rightSwap) {
        leftSwap = comparator(t[leftChild], t[rightChild]);
        rightSwap = !leftSwap;
      }

      if (leftSwap) {
        std::swap(t[pos], t[leftChild]);
        pos = leftChild;
      } else if (rightSwap) {
        std::swap(t[pos], t[rightChild]);
        pos = rightChild;
      } else {
        break; // None of the childs was swapped (or they didnt exist)
      }
    }
    return root;
  }

  void insert(const T &value) {
    if (size + 1 >= capacity) { // +1 cuz 1-indexed
      increase_capacity();
    }
    t[++size] = value;
    for (int pos = size; pos > 1; pos /= 2) {
      if (comparator(t[pos], t[pos / 2])) {
        std::swap(t[pos], t[pos / 2]);
      } else {
        break;
      }
    }
  }

  void print() {
    for (int i = 1; i <= size; i++)
      printf("%d ", t[i]);
    printf("\n");
  }

  int getSize() { return size; }
};

template <typename T> class MedianStorage {
private:
  MyHeap<T, std::greater<>> left;
  MyHeap<T, std::less<>> right;

public:
  void insert(const T &value) {
    // First insertion by definition
    if (right.getSize() == 0) {
      right.insert(value);
      return;
    }
    // Second insertion by definition, check if we need to swap values
    if (left.getSize() == 0) {
      if (value > right.getRoot()) {
        left.insert(right.getAndPopRoot());
        right.insert(value);
      } else {
        left.insert(value);
      }
      return;
    }
    // Check if belongs to left or right
    if (value < right.getRoot()) {
      left.insert(value);
    } else {
      right.insert(value);
    }
    // Balance if necessary
    if (left.getSize() > right.getSize()) {
      right.insert(left.getAndPopRoot());
    } else if (right.getSize() > left.getSize() + 1) {
      left.insert(right.getAndPopRoot());
    }
  };
  const T &getMedian() {
    return right.getRoot();
  } // Only works for odd # of elements
};

std::map<char, int> scoreMap = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
std::map<char, char> openMap = {{')', '('}, {']', '['}, {'}', '{'}, {'>', '<'}};

int main() {
  std::string line;
  MedianStorage<long> scores;

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
      long line_score = 0;
      while (!openStack.empty()) {
        line_score *= 5;
        line_score += scoreMap[openStack.top()];
        openStack.pop();
      }
      scores.insert(line_score);
    }
  }

  printf("%ld\n", scores.getMedian());

  return 0;
}
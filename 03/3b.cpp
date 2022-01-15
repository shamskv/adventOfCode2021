#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#define NBITS 12

void print_int_vector(std::vector<int> &vec) {
  for (int a : vec) {
    std::cout << a;
  }
  std::cout << std::endl;
}

std::string calculate_oxygen(std::vector<std::string> &rows, bool co2) {
  int pos_count[NBITS] = {0};
  std::vector<int> alive(rows.size(), 1);
  int n_alive = rows.size();
  int winner[NBITS] = {0};
  std::string last_alive;

  for (int i = 0; i < NBITS; i++) {
    // Calculate winner for this column
    n_alive = 0;
    for (int j = 0; j < rows.size(); j++) {
      if (alive[j]) {
        pos_count[i] += rows[j][i] - 48;
        n_alive++;
        last_alive = rows[j];
      }
    }
    if (n_alive == 1) {
      break;
    }

    winner[i] = (n_alive / 2) + (n_alive % 2 ? 1 : 0) <= pos_count[i] ? 1 : 0;
    winner[i] ^= co2;

    // Mark the losers as dead
    for (int j = 0; j < rows.size(); j++) {
      if (rows[j][i] - 48 != winner[i]) {
        alive[j] = 0;
      } else if (alive[j]) {
        last_alive = rows[j];
      }
    }
  }

  return last_alive;
}

int binary_string_to_int(std::string str) {
  if (str.size() < 1)
    return 0;
  return binary_string_to_int(str.substr(1)) +
         ((str[0] - 48) << (str.size() - 1));
}

int main() {
  int n_rows = 0;
  std::string row;

  std::vector<std::string> rows;

  while (std::cin >> row) {
    rows.push_back(row);
  }

  auto diox = binary_string_to_int(calculate_oxygen(rows, true));
  auto ox = binary_string_to_int(calculate_oxygen(rows, false));

  std::cout << ox << std::endl;
  std::cout << diox << std::endl;
  std::cout << ox * diox << std::endl;

  return 0;
}
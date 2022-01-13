#include <iostream>
#include <string>

int main() {
  std::string line;
  std::getline(std::cin, line);
  int xmin, xmax, ymin, ymax;
  sscanf(line.c_str(), "target area: x=%d..%d, y=%d..%d", &xmin, &xmax, &ymin,
         &ymax);

  int y_vel_o = std::abs(ymin) - 1;

  int y_pos = 0;
  for (int i = y_vel_o; i > 0; i--) {
    y_pos += i;
  }

  std::cout << y_pos << std::endl;

  return 0;
}
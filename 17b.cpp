#include <iostream>
#include <string>

int main() {
  std::string line;
  std::getline(std::cin, line);
  int xmin, xmax, ymin, ymax;
  sscanf(line.c_str(), "target area: x=%d..%d, y=%d..%d", &xmin, &xmax, &ymin,
         &ymax);

  // Find the minimum x speed to reach the target
  int xv_min = 0;
  while (true) {
    if (xv_min * (xv_min + 1) >= xmin) {
      break;
    }
    xv_min++;
  }

  printf("xv_min: %d\n", xv_min);

  // Find the maximum x speed to not overshoot the target
  int xv_max = xmax;

  // Find the minimum y speed to reach the target
  int yv_min = ymin;

  // Find the maximum y speed to not overshoot the target
  int yv_max = std::abs(ymin) - 1;

  // Naive approach pls work ty
  int solutions = 0;
  for (int xv_o = xv_min; xv_o <= xv_max; xv_o++) {
    for (int yv_o = yv_min; yv_o <= yv_max; yv_o++) {
      // printf("xv: %d yv: %d\n", xv_o, yv_o);
      int x = 0, y = 0;
      int xv = xv_o, yv = yv_o;
      while (x <= xmax && y >= ymin) {
        x += xv--;
        y += yv--;
        if (xv < 0) xv = 0;
        if (x >= xmin && x <= xmax && y >= ymin && y <= ymax) {
          solutions++;
          break;
        }
      }
    }
  }

  printf("solutions: %d\n", solutions);
  return 0;
}
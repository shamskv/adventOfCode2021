#include <iostream>
#include <unordered_map>

long win1 = 0;
long win2 = 0;
std::unordered_map<int, int> outcomeFrequency;

void playARound(bool first, int s1, int s2, int pos1, int pos2,
                long universes) {
  if (s1 >= 21) {
    win1 += universes;
    return;
  } else if (s2 >= 21) {
    win2 += universes;
    return;
  }

  auto branch = outcomeFrequency.begin();
  while (branch != outcomeFrequency.end()) {
    if (first) {
      int new_pos1 = ((pos1 + branch->first - 1) % 10) + 1;
      int new_s1 = s1 + new_pos1;
      playARound(!first, new_s1, s2, new_pos1, pos2,
                 universes * (branch->second));
    } else {
      int new_pos2 = ((pos2 + branch->first - 1) % 10) + 1;
      int new_s2 = s2 + new_pos2;
      playARound(!first, s1, new_s2, pos1, new_pos2,
                 universes * (branch->second));
    }
    branch++;
  }
}

int main() {
  int pos1, pos2;
  int score1 = 0, score2 = 0;
  if (!scanf("Player 1 starting position: %d\n", &pos1)) return 1;
  if (!scanf("Player 2 starting position: %d\n", &pos2)) return 1;

  for (int t1 = 1; t1 <= 3; t1++) {
    for (int t2 = 1; t2 <= 3; t2++) {
      for (int t3 = 1; t3 <= 3; t3++) {
        outcomeFrequency[t1 + t2 + t3]++;
      }
    }
  }

  playARound(true, 0, 0, pos1, pos2, 1);
  std::cout << win1 << std::endl;
  std::cout << win2 << std::endl;

  return 0;
}
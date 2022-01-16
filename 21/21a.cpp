#include <iostream>

long iter = 1;
int diceOutput() { return ((iter++ - 1) % 100) + 1; }
int rollDice() { return diceOutput() + diceOutput() + diceOutput(); };

int main() {
  int pos1, pos2;
  int score1 = 0, score2 = 0;
  if (!scanf("Player 1 starting position: %d\n", &pos1)) return 1;
  if (!scanf("Player 2 starting position: %d\n", &pos2)) return 1;

  std::cout << pos1 << " " << pos2 << std::endl;

  while (true) {
    pos1 = ((pos1 + rollDice() - 1) % 10) + 1;
    score1 += pos1;
    if (score1 >= 1000) {
      break;
    }
    pos2 = ((pos2 + rollDice() - 1) % 10) + 1;
    score2 += pos2;
    if (score2 >= 1000) {
      break;
    }
  }

  long result = std::min(score1, score2) * (iter - 1);
  std::cout << result << std::endl;

  return 0;
}
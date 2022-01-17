#include <iostream>
#include <unordered_map>
#include <utility>

struct GameState {
  bool first;
  int pos1;
  int pos2;
  int score1;
  int score2;

  GameState(bool first, int pos1, int pos2, int score1, int score2)
      : first(first), pos1(pos1), pos2(pos2), score1(score1), score2(score2){};

  std::string hashLOL() const {
    char buff[100] = {0};
    sprintf(buff, "%d,%d,%d,%d,%d", first, pos1, pos2, score1, score2);
    return {buff};
  }

  bool operator==(const GameState &o) const {
    return first == o.first && pos1 == o.pos1 && pos2 == o.pos2 &&
           score1 == o.score1 && score2 == o.score2;
  }
};

template <>
struct std::hash<GameState> {
  std::size_t operator()(GameState const &c) const noexcept {
    return std::hash<std::string>{}(c.hashLOL());
  }
};

typedef std::pair<long, long> winCount;

std::unordered_map<GameState, winCount> stateResults;
std::unordered_map<int, int> outcomeFrequency;

winCount play(GameState state) {
  if (state.score1 >= 21) {
    return std::make_pair(1, 0);
  } else if (state.score2 >= 21) {
    return std::make_pair(0, 1);
  }

  auto storedResults = stateResults.find(state);
  if (storedResults != stateResults.end()) {
    return storedResults->second;
  }
  winCount results = {0, 0};

  auto branch = outcomeFrequency.begin();
  while (branch != outcomeFrequency.end()) {
    winCount r;
    if (state.first) {
      int new_pos1 = ((state.pos1 + branch->first - 1) % 10) + 1;
      int new_s1 = state.score1 + new_pos1;
      r = play({!state.first, new_pos1, state.pos2, new_s1, state.score2});
    } else {
      int new_pos2 = ((state.pos2 + branch->first - 1) % 10) + 1;
      int new_s2 = state.score2 + new_pos2;
      r = play({!state.first, state.pos1, new_pos2, state.score1, new_s2});
    }
    results.first += (branch->second * r.first);
    results.second += (branch->second * r.second);
    branch++;
  }

  stateResults[state] = results;
  return results;
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

  auto r = play({true, pos1, pos2, 0, 0});
  std::cout << r.first << std::endl;
  std::cout << r.second << std::endl;

  return 0;
}
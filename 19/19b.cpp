#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
////////////////////////////////////////////////////////////////
// Class + methods to deal with 3d coordinates                //
////////////////////////////////////////////////////////////////
class Coordinates {
 public:
  int x, y, z;

  Coordinates(int x, int y, int z) : x(x), y(y), z(z){};

  std::string hashLOL() const {
    char buff[100] = {0};
    sprintf(buff, "%d,%d,%d", x, y, z);
    std::string ret(buff);
    return ret;
  }

  void print() const { printf("%d %d %d\n", x, y, z); }

  bool operator==(const Coordinates &other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }
};

template <>
struct std::hash<Coordinates> {
  std::size_t operator()(Coordinates const &c) const noexcept {
    return std::hash<std::string>{}(c.hashLOL());
  }
};

Coordinates operator+(const Coordinates &lhs, const Coordinates &rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

int dist(Coordinates &p1, Coordinates &p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) +
         (p1.z - p2.z) * (p1.z - p2.z);
}

Coordinates diff(Coordinates &p1, Coordinates &p2) {
  return {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
}

long manhattan_dist(Coordinates const &p1, Coordinates const &p2) {
  return std::abs(p2.x - p1.x) + std::abs(p2.y - p1.y) + std::abs(p2.z - p1.z);
}

/////////////////////////////////////////////////////////////////////
// Scanner class that stores all readings + distance between them  //
/////////////////////////////////////////////////////////////////////
class Scanner {
 public:
  int id;
  Coordinates offset;
  std::vector<Coordinates> readings;
  std::vector<std::multiset<int>> readingsDistance;

  Scanner(int id) : id(id), offset(0, 0, 0){};

  void createReadingsDistanceMatrix() {
    // redundant but makes it easier
    for (int i = 0; i < readings.size(); i++) {
      readingsDistance.emplace_back();
      for (int j = 0; j < readings.size(); j++) {
        if (i == j) continue;
        readingsDistance.back().insert(dist(readings[i], readings[j]));
      }
    }
  }
  void roll() {
    for (auto &r : readings) {
      r = Coordinates(r.x, r.z, -r.y);
    }
  }

  void turn() {
    for (auto &r : readings) {
      r = Coordinates(-r.y, r.x, r.z);
    }
  }

  void addOffset(Coordinates &value) {
    for (auto &r : readings) {
      r = r + value;
    }
  }
};

////////////////////////////////////////////////////////////////
// Intersects readings between two scanners                   //
////////////////////////////////////////////////////////////////
auto intersectReadings(Scanner &s1, Scanner &s2) {
  std::vector<std::pair<int, int>> commonReadings;
  for (int i1 = 0; i1 < s1.readingsDistance.size(); i1++) {
    for (int i2 = 0; i2 < s2.readingsDistance.size(); i2++) {
      std::vector<int> intersections;
      std::set_intersection(
          s1.readingsDistance[i1].begin(), s1.readingsDistance[i1].end(),
          s2.readingsDistance[i2].begin(), s2.readingsDistance[i2].end(),
          std::back_inserter(intersections));
      if (intersections.size() >= 11) {
        commonReadings.emplace_back(i1, i2);
        break;
      }
    }
  }
  return commonReadings;
}

//////////////////////////////////////////////////////////////////
// Tries to find a common distance between two sets of readings //
//////////////////////////////////////////////////////////////////
std::optional<Coordinates> calculateDistance(
    Scanner &s1, Scanner &s2, std::vector<std::pair<int, int>> commonReadings) {
  std::optional<Coordinates> lastValue;
  for (auto &pair : commonReadings) {
    Coordinates result = diff(
        s2.readings[pair.second],
        s1.readings[pair.first]);  // ELP, idk why this only works in this order
    if (lastValue) {
      if (!(*lastValue == result)) return std::nullopt;
    } else {
      lastValue = result;
    }
  }
  return lastValue;
}

//////////////////////////////////////////////////////////////////////////
// Goes over rotations of scanner 2 to until a common distance is found //
// https://stackoverflow.com/a/16467849/5537771 thx a lot               //
//////////////////////////////////////////////////////////////////////////
void positionSecondScanner(Scanner &s1, Scanner &s2,
                           std::vector<std::pair<int, int>> commonReadings) {
  for (int cycle = 0; cycle < 2; cycle++) {
    for (int step = 0; step < 3; step++) {
      s2.roll();
      auto match = calculateDistance(s1, s2, commonReadings);
      if (match) {
        s2.offset = match.value();
        s2.addOffset(match.value());
        return;
      }
      for (int i = 0; i < 3; i++) {
        s2.turn();
        auto match = calculateDistance(s1, s2, commonReadings);
        if (match) {
          s2.offset = match.value();
          s2.addOffset(match.value());
          return;
        }
      }
    }
    s2.roll();
    s2.turn();
    s2.roll();
  }

  printf("Tried to position an incorrect scanner, ids: %d %d\n", s1.id, s2.id);
  throw std::exception();
}

int main() {
  std::string line;
  std::vector<Scanner> scannerList;
  int idCounter = 0;
  /////////////////////////////////////////
  // Read input and create scanner list  //
  /////////////////////////////////////////
  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;
    if (line[1] == '-') {
      scannerList.emplace_back(idCounter++);
      continue;
    }
    int x, y, z;
    if (sscanf(line.c_str(), "%d,%d,%d", &x, &y, &z) != 3) {
      printf("problem with line first char %d\n", line[0]);
      continue;
    }
    scannerList.back().readings.emplace_back(x, y, z);
  }
  for (auto &b : scannerList) {
    b.createReadingsDistanceMatrix();
  }

  //////////////////////////////////////////////////
  // Start at scanner 0 and recursively correct   //
  // the readings for other scanners              //
  //////////////////////////////////////////////////
  std::vector<bool> visited(scannerList.size(), false);
  visited[0] = true;
  std::stack<int> correct;
  correct.push(0);
  while (!correct.empty()) {
    int s0 = correct.top();
    correct.pop();
    printf("visiting scanner %d\n", s0);
    for (int s1 = 0; s1 < scannerList.size(); s1++) {
      if (visited[s1]) continue;
      auto commonReadings = intersectReadings(scannerList[s0], scannerList[s1]);
      if (commonReadings.size() >= 12) {
        printf("intersection between scanners %d and %d\n", s0, s1);
        positionSecondScanner(scannerList[s0], scannerList[s1], commonReadings);
        visited[s1] = true;
        correct.push(s1);
      }
    }
  }

  Coordinates furthest{0, 0, 0};
  long furthestValue = 0;
  std::unordered_set<Coordinates> beacons;
  for (auto &s : scannerList) {
    for (auto &b : s.readings) {
      beacons.insert(b);
    }
    // We can pick the scanner furthest away from the origin to save the
    // quadratic complexity later
    long man = manhattan_dist(Coordinates{0, 0, 0}, s.offset);
    if (man > furthestValue) {
      furthest = s.offset;
      furthestValue = man;
    }
  }

  auto it = scannerList.begin();
  while (it != scannerList.end()) {
    furthestValue =
        std::max(furthestValue, manhattan_dist(furthest, (it++)->offset));
  }

  std::cout << beacons.size() << std::endl;
  std::cout << furthestValue << std::endl;

  return 0;
}
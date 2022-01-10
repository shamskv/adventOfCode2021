#include <iostream>
#include <string>
#include <vector>

// Copied from SO
unsigned char hexchar2byte(char input) {
  if (input >= '0' && input <= '9') return input - '0';
  if (input >= 'A' && input <= 'F') return input - 'A' + 10;
  if (input >= 'a' && input <= 'f') return input - 'a' + 10;
  throw std::invalid_argument("Invalid input string");
}

class MyBitStream {
 private:
  long pos = 0;
  std::string data;

 public:
  MyBitStream(const std::string& inputData) : data(inputData) {}
  unsigned int getNextBits(int n) {
    unsigned int output = 0;
    for (int i = 0; i < n; i++) {
      auto curr_byte = hexchar2byte(data[(pos + i) / 4]);
      char curr_bit = (curr_byte >> (3 - ((pos + i) % 4))) & 0b1;
      output += curr_bit << (n - i - 1);
    }
    pos += n;
    return output;
  }
  long getPos() { return pos; }
};

class Packet {
 private:
  // Common
  int version = 0;
  int typeId = 0;
  long length = 0;
  // Non literal
  int lengthTypeId = 0;
  union {
    int subPacketLength;
    int subPacketNum;
  };
  std::vector<Packet> subPackets;
  // Literal
  std::vector<long> values;

 public:
  Packet(MyBitStream& stream);

  int computeVersion();
  long valueAsLong();
  long compute();
};

Packet::Packet(MyBitStream& stream) {
  auto startPos = stream.getPos();
  this->version = stream.getNextBits(3);
  this->typeId = stream.getNextBits(3);

  if (this->typeId == 4) {
    int control;
    do {
      auto block = stream.getNextBits(5);
      control = block & 0x10;
      int val = block & 0x0F;
      values.push_back(val);
    } while (control);
  } else {
    this->lengthTypeId = stream.getNextBits(1);
    if (lengthTypeId) {
      subPacketNum = stream.getNextBits(11);
      for (int i = 0; i < subPacketNum; i++) {
        subPackets.emplace_back(stream);
      }
    } else {
      subPacketLength = stream.getNextBits(15);
      auto targetPos = stream.getPos() + subPacketLength;
      while (stream.getPos() < targetPos) {
        subPackets.emplace_back(stream);
      }
    }
  }

  auto endPos = stream.getPos();
  this->length = endPos - startPos;
}

long Packet::valueAsLong() {
  long sum = 0;
  for (int i = 0; i < values.size(); i++) {
    sum += values[i] << ((values.size() - i - 1) * 4);
  }
  return sum;
}

int Packet::computeVersion() {
  int sum = version;
  for (auto& c : subPackets) {
    sum += c.computeVersion();
  }
  return sum;
}

long Packet::compute() {
  if (typeId == 0) {
    long sum = 0;
    for (auto& c : subPackets) {
      sum += c.compute();
    }
    return sum;
  } else if (typeId == 1) {
    long mult = 1;
    for (auto& c : subPackets) {
      mult *= c.compute();
    }
    return mult;
  } else if (typeId == 2) {
    long min = INT64_MAX;
    for (auto& c : subPackets) {
      min = std::min(min, c.compute());
    }
    return min;
  } else if (typeId == 3) {
    long max = INT64_MIN;
    for (auto& c : subPackets) {
      max = std::max(max, c.compute());
    }
    return max;
  } else if (typeId == 4) {
    return valueAsLong();
  } else if (typeId == 5) {
    return subPackets[0].compute() > subPackets[1].compute() ? 1 : 0;
  } else if (typeId == 6) {
    return subPackets[0].compute() < subPackets[1].compute() ? 1 : 0;
  } else if (typeId == 7) {
    return subPackets[0].compute() == subPackets[1].compute() ? 1 : 0;
  } else {
    throw std::exception();
  }
}

int main() {
  std::string line;
  std::cin >> line;
  MyBitStream stream(line);

  Packet p(stream);

  std::cout << p.compute() << std::endl;

  return 0;
}
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Node {
public:
  std::shared_ptr<Node> next;
  std::string value;

  Node(std::string v) : value(v){};

  void insertAfter(std::string v) {
    auto new_node = std::make_shared<Node>(v);
    if (next) {
      new_node->next = std::move(this->next);
    }
    this->next = std::move(new_node);
  }
};

std::shared_ptr<Node> head;
std::shared_ptr<Node> tail;

std::unordered_map<std::string, std::string> mappings;

void printll(std::shared_ptr<Node> head) {
  std::unordered_map<std::string, long> frequency;
  long n = 0;
  while (head) {
    // std::cout << head->value;
    frequency[head->value]++;
    head = head->next;
    n++;
  }
  long max = INT64_MIN, min = INT64_MAX;
  auto it = frequency.begin();
  while (it != frequency.end()) {
    std::cout << it->first << " " << it->second << std::endl;
    max = std::max(max, it->second);
    min = std::min(min, it->second);
    it++;
  }
  std::cout << n << " " << min << " " << max << " " << max - min << " "
            << std::endl;
}

int main() {

  std::string line;

  std::cin >> line;

  for (auto &c : line) {
    if (!head) {
      head = std::make_shared<Node>(std::string(1, c));
      tail = head;
    } else {
      tail->insertAfter(std::string(1, c));
      tail = tail->next;
    }
  }

  while (std::cin >> line) {
    std::string line2;
    std::cin >> line2;
    std::cin >> line2;

    mappings[line] = line2;
  }

  printll(head);
  for (int i = 0; i < 10; i++) {
    auto runner = head;
    while (runner->next) {
      auto next_node = runner->next;
      std::string pair = runner->value + runner->next->value;
      if (mappings.find(pair) != mappings.end()) {
        runner->insertAfter(mappings[pair]);
      }
      runner = next_node;
    }
    printll(head);
  }

  return 0;
}
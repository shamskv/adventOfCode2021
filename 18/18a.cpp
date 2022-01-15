#include <iostream>
#include <memory>
#include <stack>
#include <string>

enum NodeType { SNAIL, VALUE };

class Node {
 public:
  NodeType type;
  std::shared_ptr<Node> leftChild;
  std::shared_ptr<Node> rightChild;
  int value;

  Node() : type(SNAIL){};
  Node(int v) : type(VALUE), value(v){};
  Node(int v1, int v2) : type(SNAIL) {
    leftChild = std::make_shared<Node>(v1);
    rightChild = std::make_shared<Node>(v2);
  };

  void split() {
    if (type == VALUE) {
      type = SNAIL;
      leftChild = std::make_shared<Node>(value / 2);
      rightChild = std::make_shared<Node>(value / 2 + (value % 2));
    }
  }

  std::pair<int, int> explode() {
    if (leftChild->type != VALUE || rightChild->type != VALUE) {
      printf("gg\n");
    }

    type = VALUE;
    value = 0;
    auto pairToReturn = std::make_pair(leftChild->value, rightChild->value);

    leftChild.reset();
    rightChild.reset();

    return pairToReturn;
  }

  void printNode() {
    if (type == VALUE) {
      std::cout << value;
    } else {
      std::cout << "[";
      leftChild->printNode();
      std::cout << ",";
      rightChild->printNode();
      std::cout << "]";
    }
  }

  long magnitude() {
    if (type == VALUE) {
      return value;
    } else {
      return leftChild->magnitude() * 3 + rightChild->magnitude() * 2;
    }
  }
};
typedef std::shared_ptr<Node> NodePtr;
typedef std::pair<NodePtr, int> NodePtrWithDepth;

bool explodeTree(NodePtr root) {
  std::stack<NodePtrWithDepth> stack;
  stack.emplace(root, 0);
  NodePtr lastValue;
  int toAdd = -1;
  bool exploded = false;
  while (!stack.empty()) {
    // Check top of stack
    auto top = stack.top();
    stack.pop();
    auto currentNode = top.first;
    auto depth = top.second;

    if (depth >= 4 && !exploded && currentNode->type == SNAIL) {
      exploded = true;
      auto shrapnel = currentNode->explode();
      if (lastValue) {
        lastValue->value += shrapnel.first;
      }
      toAdd = shrapnel.second;
      continue;
    }

    if (currentNode->type == VALUE) {
      if (toAdd != -1) {
        currentNode->value += toAdd;
        break;
      } else {
        lastValue = currentNode;
      }
    } else {
      // Add childs
      stack.emplace(currentNode->rightChild, depth + 1);
      stack.emplace(currentNode->leftChild, depth + 1);
    }
  }
  return exploded;
}

bool splitTree(NodePtr root) {
  std::stack<NodePtr> stack;
  stack.push(root);
  while (!stack.empty()) {
    auto currentNode = stack.top();
    stack.pop();
    if (currentNode->type == VALUE) {
      if (currentNode->value >= 10) {
        currentNode->split();
        return true;
      }
    } else {
      // Add childs
      stack.emplace(currentNode->rightChild);
      stack.emplace(currentNode->leftChild);
    }
  }
  return false;
}

void reduceTree(NodePtr root) {
  while (true) {
    if (explodeTree(root)) continue;
    if (splitTree(root)) continue;
    break;
  }
}

int main() {
  std::string line;

  std::stack<NodePtr> stack;
  std::stack<bool> leftStack;
  NodePtr root = std::make_shared<Node>();
  stack.push(root);
  stack.push(root);
  leftStack.push(false);
  leftStack.push(true);

  bool firstRead = true;
  while (std::cin >> line) {
    // Read current line
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ',' || line[i] == ']') continue;
      auto currentNode = stack.top();
      auto leftChild = leftStack.top();
      stack.pop();
      leftStack.pop();

      if (line[i] == '[') {
        NodePtr newNode = std::make_shared<Node>();
        stack.push(newNode);
        stack.push(newNode);
        leftStack.push(false);
        leftStack.push(true);
        if (leftChild) {
          currentNode->leftChild = newNode;
        } else {
          currentNode->rightChild = newNode;
        }
      } else if (line[i] >= '0' && line[i] <= '9') {
        NodePtr newNode = std::make_shared<Node>(line[i] - '0');
        if (leftChild) {
          currentNode->leftChild = newNode;
        } else {
          currentNode->rightChild = newNode;
        }
      }
    }

    // If it's the first read move on, if not we need to place all new stuff
    // in a new root after reducing
    if (!firstRead) {
      reduceTree(root);
      NodePtr newRoot = std::make_shared<Node>();
      newRoot->leftChild = root;
      root = newRoot;
      stack.push(newRoot);
      leftStack.push(false);
    } else {
      firstRead = false;
    }
  }

  root->leftChild->printNode();
  printf("\n");
  std::cout << root->leftChild->magnitude() << std::endl;
  return 0;
}
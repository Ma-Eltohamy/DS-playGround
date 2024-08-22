#include <iostream>

struct Node {
  Node(int data) : data(data) {}
  Node *right{};
  Node *left{};
  int data{};

  ~Node() {
    std::cout << "\n==> Destroy value: " << data << " at address " << this
              << '\n';
  }
};

int treeMax(Node *cur) {
  if (!cur)
    return -1;

  int leftMax{std::max(cur->data, treeMax(cur->left))};
  int rightMax{std::max(cur->data, treeMax(cur->right))};

  return std::max(leftMax, rightMax);
}

void clear(Node *cur) {
  if (!cur)
    return;

  // deletation will just be allowed in the post order way
  clear(cur->left);
  clear(cur->right);
  delete cur;
}
int main(int argc, char *argv[]) {
  // some operations

  Node *node1{new Node(1)};
  Node *node2{new Node(2)};
  Node *node3{new Node(3)};
  Node *node4{new Node(4)};
  Node *node5{new Node(5)};
  Node *node6{new Node(6)};
  Node *node7{new Node(7)};
  Node *node8{new Node(8)};
  Node *node9{new Node(9)};
  Node *node10{new Node(10)};
  // Node *node11{new Node(11)};

  node1->left = node2;
  node1->right = node3;

  node2->left = node4;
  node2->right = node5;

  node4->left = node7;
  node4->right = node8;

  node5->right = node9;
  // node5->left = node11;

  node3->right = node6;

  node6->left = node10;

  // node10->right = node11;

  std::cout << treeMax(nullptr) << '\n';

  clear(node1);
  return 0;
}

#include <algorithm>
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

void printInOrder(Node *cur) {
  if (!cur)
    return;

  printInOrder(cur->left);
  std::cout << cur->data << ' ';
  printInOrder(cur->right);
}

void printPostOrder(Node *cur) {
  if (!cur)
    return;

  printPostOrder(cur->left);
  printPostOrder(cur->right);
  std::cout << cur->data << ' ';
}

void printPreOrder(Node *cur) {
  if (!cur)
    return;

  std::cout << cur->data << ' ';
  printPreOrder(cur->left);
  printPreOrder(cur->right);
}

int treeMin(Node *cur) {
  if (!cur)
    return -1;
  if (!cur->left || !cur->right)
    return cur->data;

  int leftSide{std::min(cur->data, treeMin(cur->left))};
  int rightSide{std::min(cur->data, treeMin(cur->right))};

  return std::min(leftSide, rightSide);
}

int treeHeight(Node *cur) {
  if (!cur)
    return -1;

  int leftSide{treeHeight(cur->left)};
  int rightSide{treeHeight(cur->right)};

  return std::max(leftSide, rightSide) + 1;
}

int countleafs(Node *cur) {
  if (!cur)
    return 0;
  else if (!cur->left && !cur->right) {
    std::cout
        << cur->data
        << ' '; // will print 10 9 8 7 4 (4) is the number of leafs in the tree
    return 1;
  }

  return countleafs(cur->right) + countleafs(cur->left);
}

// not done yet
int countNonLeafs(Node *cur) {
  if (!cur || (!cur->left && !cur->right))
    return 0;

  return countNonLeafs(cur->left) + countNonLeafs(cur->right) + 1;
}

void clear(Node *cur) {
  if (!cur)
    return;

  // deletation will just be allowed in the post order way
  clear(cur->left);
  clear(cur->right);
  delete cur;
  cur = nullptr;
}
int main(int argc, char *argv[]) {
  // some operations

  // Node *plus(new Node('+'));
  // Node *node2(new Node('2'));
  // Node *node3(new Node('3'));
  // plus->left = node2;
  // plus->right = node3;
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

  // printInOrder(plus);
  // std::cout << std::endl;
  // printPostOrder(plus);
  // std::cout << std::endl;
  // printPreOrder(plus);
  // std::cout << std::endl;
  //

  Node *nullNode{};
  std::cout << "\nNonLeafs Number in the tree is: " << countNonLeafs(node1)
            << '\n';
  std::cout << "\nLeafs Number in the tree is: " << countleafs(node1) << '\n';
  std::cout << "\nHeight of the tree is: " << treeHeight(node1) << '\n';
  std::cout << "\nMinmum Value in the tree is: " << treeMin(node1) << '\n';
  std::cout << "\nPrinting In Order: ";
  printInOrder(node1);
  std::cout << std::endl;
  std::cout << "\nPrinting Post Order: ";
  printPostOrder(node1);
  std::cout << std::endl;
  std::cout << "\nPrinting Pre Order: ";
  printPreOrder(node1);
  std::cout << std::endl;
  clear(node1);
  return 0;
}

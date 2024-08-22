#include <assert.h>
#include <iostream>
#include <queue>

struct Node {
  Node *left{};
  Node *right{};

  int val{};
  int height{};

  Node(int val) : val(val) {}

  int getHeight(Node *root) {
    if (!root)
      return -1;
    return root->height;
  }

  void updataHeight() {
    height = 1 + std::max(getHeight(left), getHeight(right));
  }

  int balanceFactor() {
    int bf{getHeight(left) - getHeight(right)};
    return bf;
  }
};

class AVLTree {
private:
  Node *root{};

  Node *_insert(int value, Node *root) {
    if (!root)
      return new Node(value);
    if (value > root->val)
      root->right = _insert(value, root->right);
    else if (value <= root->val)
      root->left = _insert(value, root->left);

    root->updataHeight();
    return balance(root);
  }

  Node *_delete(int target, Node *root) {
    if (target > root->val)
      root->right = _delete(target, root->right);
    else if (target < root->val)
      root->left = _delete(target, root->left);
    else { // Found target
      Node *tmp{root};
      // If it has no children
      if (!root->right && !root->left)
        root = nullptr;
      else if (!root->right) // Has one child on left
        root = root->left;
      else if (!root->left) // Has one child on right
        root = root->right;
      else { // So, It has (2) two children 100% has successor
        Node *successor{min(root->right)};
        root->val = successor->val;
        root->right = _delete(successor->val, root->right);
        tmp = nullptr;
      }
      if (tmp)
        delete tmp;
    }

    if (root) { // If Found a target
      root->updataHeight();
      root = balance(root);
    }
    return root;
  }

  Node *_search(int value, Node *root) {
    if (!root)
      return nullptr;

    if (value == root->val)
      return root;
    if (value > root->val)
      return _search(value, root->right);
    return _search(value, root->left);
  }

  Node *min(Node *root) {
    if (!root)
      return nullptr;
    if (root->left)
      return min(root->left);
    return root;
  }
  Node *max(Node *root) {
    if (!root)
      return nullptr;

    if (root->right)
      return max(root->right);
    return root;
  }

  void _printSorted(Node *root) { // print Inorder
    if (root->left)
      _printSorted(root->left);
    std::cout << root->val << ' ';
    if (root->right)
      _printSorted(root->right);
  }

  Node *rightRotate(Node *root) {
    if (!root->left)
      return nullptr;

    Node *tmp{root->left};
    root->left = tmp->right;
    tmp->right = root;

    root->updataHeight();
    tmp->updataHeight();

    return tmp;
  }

  Node *leftRotate(Node *root) {
    if (!root->right)
      return nullptr;

    Node *tmp{root->right};
    root->right = tmp->left;
    tmp->left = root;

    root->updataHeight();
    tmp->updataHeight();

    return tmp;
  }

  Node *balance(Node *root) {
    if (root->balanceFactor() == 2) { // Then my left is taller than right
      if (root->left->balanceFactor() == -1) // See if left has -1
        root->left =
            leftRotate(root->left); // if left is -1 the make left rotate
      root = rightRotate(root);
    } else if (root->balanceFactor() == -2) {
      if (root->right->balanceFactor() == 1)
        root->right = rightRotate(root->right);
      root = leftRotate(root);
    }
    return root;
  }

public:
  void insert(int value) {
    if (!root)
      root = new Node(value);
    else
      root = _insert(value, root);
  }

  void deleteValue(int value) {
    if (!root)
      return;
    else
      root = _delete(value, root);
  }

  bool search(int value) {
    if (_search(value, root))
      return true;
    return false;
  }

  int minValue() {
    assert(root);
    return min(root)->val;
  }
  int maxValue() {
    assert(root);
    return max(root)->val;
  }

  void printSorted() {
    if (!root)
      return;
    else {
      _printSorted(root);
      std::cout << '\n';
    }
  }

  void levelOrderTraversal() {
    if (!root)
      return;

    std::cout << "******************\n";
    std::queue<Node *> nodes_queue;
    nodes_queue.push(root);

    int level = 0;
    while (!nodes_queue.empty()) {
      int sz = nodes_queue.size();

      std::cout << "Level " << level << ": ";
      while (sz--) {
        Node *cur = nodes_queue.front();
        nodes_queue.pop();

        std::cout << cur->val << " ";
        if (cur->left)
          nodes_queue.push(cur->left);
        if (cur->right)
          nodes_queue.push(cur->right);
      }
      level++;
      std::cout << "\n";
    }
  }
};

void f1() {
  AVLTree tree;

  for (int i = 0; i <= 32; ++i) { // degenerate
    tree.insert(i);
    tree.levelOrderTraversal();
  }

  std::cout << tree.maxValue() << std::endl;
  std::cout << tree.minValue() << std::endl;
}

int main() {
  f1();

  std::cout << "bye\n";

  return 0;
}

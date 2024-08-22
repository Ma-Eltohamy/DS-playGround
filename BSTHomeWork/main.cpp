#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct TreeNode {
  int val{};
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(int val) : val(val) {}
};

struct BinaryTree {
  TreeNode *root{};
  BinaryTree(int root_value) : root(new TreeNode(root_value)) {}

  void add(vector<int> values, vector<char> direction) {
    assert(values.size() == direction.size());
    TreeNode *current = this->root;
    // iterate on the path, create all necessary TreeNodes
    for (int i = 0; i < (int)values.size(); ++i) {
      if (direction[i] == 'L') {
        if (!current->left)
          current->left = new TreeNode(values[i]);
        else
          assert(current->left->val == values[i]);
        current = current->left;
      } else {
        if (!current->right)
          current->right = new TreeNode(values[i]);
        else
          assert(current->right->val == values[i]);
        current = current->right;
      }
    }
  }

  void _print_inorder(TreeNode *current) {
    if (!current)
      return;
    _print_inorder(current->left);
    cout << current->val << " ";
    _print_inorder(current->right);
  }

  void print_inorder() {
    _print_inorder(root);
    cout << "\n";
  }

  bool _search(TreeNode *root, int target) { // tail recursion
    if (!root)
      return false;

    if (target == root->val)
      return true;

    if (target < root->val)
      return _search(root->left, target);

    return _search(root->right, target);
  }

  bool search(int target) { return _search(root, target); }

  // My insertion method
  void _insert(TreeNode *&root, int &value) {
    if (!root)
      root = new TreeNode(value);

    if (root->val > value)
      _insert(root->left, value);
    else if (root->val < value)
      _insert(root->right, value);
  }
  void insert(int value) { _insert(root, value); }

  int _min(TreeNode *root) {
    if (root->left)
      return _min(root->left);
    return root->val;
  }
  int min() {
    if (!root)
      return -1;
    return _min(root);
  }

  int _max(TreeNode *root) {
    if (root->right)
      return _max(root->right);
    return root->val;
  }
  int max() {
    if (!root)
      return -1;
    return _max(root);
  }

  bool findChain(TreeNode *root, int target,
                 std::vector<TreeNode *> &ancestors) {
    ancestors.push_back(root);

    if (root->val == target)
      return true;

    if (root->val > target)
      return root->left && findChain(root->left, target, ancestors);

    return root->right && findChain(root->right, target, ancestors);
  }

  TreeNode *getNext(std::vector<TreeNode *> &ancestors) {
    if (ancestors.empty())
      return nullptr;

    TreeNode *cur{ancestors.back()};
    ancestors.pop_back();
    return cur;
  }

  std::pair<bool, int> successor(int target) {
    std::vector<TreeNode *> ancestors;
    bool isFound{findChain(root, target, ancestors)};

    if (!isFound)
      return std::make_pair(false, -1);

    // if(isFound) --> Then, ancestors had all ancestors of found node, and the
    // last node is our target
    TreeNode *child{getNext(ancestors)};

    if (child->right)
      return std::make_pair(true, _min(root->right));

    // Doesn't have right Then, return back through all parents and till found
    // my successor parent
    TreeNode *parent{getNext(ancestors)};
    // While there's a prent and the child is it's right one then climb up the
    // chain
    while (parent && parent->right == child)
      child = parent, parent = getNext(ancestors);

    if (parent) // If found parent after this loop means that we got our
                // successor
      return std::make_pair(true, parent->val);
    return std::make_pair(false, -1);
  }
};

int main() {
  BinaryTree tree(50);
  tree.insert(20);
  tree.insert(45);
  tree.insert(70);
  tree.insert(73);
  tree.insert(35);
  tree.insert(15);
  tree.insert(60);

  // tree.print_inorder();
  vector<int> v{15, 20, 35, 45, 50, 60, 70, 73, 100};

  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
    pair<bool, int> p = tree.successor(v[i]);

    if (p.first)
      cout << p.second << "\n";
    else
      cout << "NA\n";
  }

  cout << "bye\n";
  return 0;
}

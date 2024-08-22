#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct TreeNode {
  int val{};
  TreeNode *left{};
  TreeNode *right{};
  TreeNode *parent{};
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

  int _min(TreeNode *root) {
    while (root && root->left)
      root = root->left;
    return root->val;
  }
  int min() { return _min(root); }

  void _insert(TreeNode *&root, int val) {
    if (!root) {
      root = new TreeNode(val);
      return;
    }

    if (val < root->val)
      _insert(root->left, val);
    else
      _insert(root->right, val);
  }

  void insert(int val) {
    if (!root)
      root = new TreeNode(val);
    else
      _insert(root, val);
  }

  bool findChain(int target, std::vector<TreeNode *> &anscestors) {
    TreeNode *cur{root};
    bool isFound{false};

    while (cur && !isFound) {
      if (target > cur->val)
        cur = cur->right;
      else {
        anscestors.push_back(cur);
        if (target == cur->val)
          isFound = true;
        else
          cur = cur->left;
      }
    }
    return isFound;
  }

  TreeNode *getNext(std::vector<TreeNode *> &anscestors) {
    if (anscestors.empty())
      return nullptr;
    TreeNode *cur{anscestors.back()};
    anscestors.pop_back();
    return cur;
  }

  std::pair<bool, int> successor(int val) {
    std::vector<TreeNode *> anscestors;
    if (!findChain(val, anscestors))
      return std::make_pair(false, -1);

    TreeNode *child{getNext(anscestors)};
    if (child->right)
      return make_pair(true, _min(child->right));

    TreeNode *parent{getNext(anscestors)};

    if (parent)
      return std::make_pair(true, parent->val);
    return std::make_pair(false, -1);
  }
};
class Solution {
public:
};

int main(int argc, char *argv[]) {
  BinaryTree tree(50);
  tree.insert(20);
  tree.insert(45);
  tree.insert(70);
  tree.insert(73);
  tree.insert(35);
  tree.insert(15);
  tree.insert(60);

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

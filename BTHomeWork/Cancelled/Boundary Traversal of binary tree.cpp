#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

struct TreeNode {
  TreeNode(int val) : val(val) {}
  TreeNode *right{};
  TreeNode *left{};
  int val{};

  ~TreeNode() {
    std::cout << "\n==> Destroy value: " << val << " at address " << this
              << '\n';
  }
};

struct BinaryTree {
  TreeNode *root{};
  BinaryTree(TreeNode *root) : root(root) {}
  BinaryTree(int root_value) : root(new TreeNode(root_value)) {}

  void add(std::vector<int> values, std::vector<char> direction) {
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

  void _printInorder(TreeNode *current) {
    if (!current)
      return;
    _printInorder(current->left);
    std::cout << current->val << " ";
    _printInorder(current->right);
  }

  void printInorder() {
    _printInorder(root);
    std::cout << "\n";
  }

  void _clear(TreeNode *cur) {
    if (!cur)
      return;

    _clear(cur->left), _clear(cur->right);
    delete cur;
  }

  void clear() {
    _clear(root);
    std::cout << "\nTree has been cleaned.\n";
  }
};

class Solution {
public:
  void leftBoundaryNodes(TreeNode *root, std::vector<int> &v) {
    if (!root)
      return;

    if (root->left) { // so it's a node
      v.push_back(root->val);
      leftBoundaryNodes(root->left, v);
    } else if (root->right) {
      v.push_back(root->val);
      leftBoundaryNodes(root->right, v);
    }
  }

  void rightBoundaryNodes(TreeNode *root, std::vector<int> &v) {
    if (!root)
      return;

    if (root->right) { // so it's a node
      // We want to get right boundary from bottome to up so go deep as you can
      // then push when you return back
      rightBoundaryNodes(root->right, v);
      v.push_back(root->val);
    } else if (root->left) {
      rightBoundaryNodes(root->left, v);
      v.push_back(root->val);
    }
  }

  bool isleaf(TreeNode *root) {
    if (!root->left && !root->right)
      return true;
    return false;
  }
  void BoundaryLeaves(TreeNode *root, std::vector<int> v) {
    if (!root)
      return;
    // First, go left as much as you can to get the most left leaf
    // Then, Check our if i'm a leaf
    // Finally, go right as much as you can to get the most right leaf
    BoundaryLeaves(root->left, v);
    if (!root->left && !root->right)
      v.push_back(root->val);
    BoundaryLeaves(root->right, v);
  }

  std::vector<int> boundary(TreeNode *root) {
    std::vector<int> v;
    if (!root)
      return v;

    v.push_back(root->val);

    leftBoundaryNodes(root->left, v);

    BoundaryLeaves(root->left, v);
    BoundaryLeaves(root->right, v);

    rightBoundaryNodes(root->right, v);

    return v;
  }
};

int main() {

  std::vector<std::string> leetCodeSerializedTree = {};

  std::cout << "\nbye\n";

  return 0;
}

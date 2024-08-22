#include <cassert>
#include <iostream>
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
};
class Solution {
public:
  void _kthSmallest(TreeNode *root, int &k, int &res) {
    if (!root)
      return;

    _kthSmallest(root->left, k, res);
    if (k == 1)
      res = root->val;
    --k;
    _kthSmallest(root->right, k, res);
  }

  int kthSmallest(TreeNode *root, int k) {
    int res{-1234};
    _kthSmallest(root, k, res);
    return res;
  }
};

int main(int argc, char *argv[]) {
  BinaryTree tree(3);
  tree.add({1}, {'L'});
  tree.add({1, 2}, {'L', 'R'});
  tree.add({4}, {'R'});
  int k = 1, res = -1234;
  std::cout << Solution().kthSmallest(tree.root, k, res);
  return 0;
}

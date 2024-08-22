#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iostream>
#include <tuple>
#include <utility>
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
  bool isLeaf(TreeNode *root) { return !root->left && !root->right; }
  bool isFull(TreeNode *root) {

    if (!root)
      return false;
    if (isLeaf(root))
      return true;
    if ((root->right && !root->left) || (!root->right && root->left))
      return false;

    return isFull(root->left) && isFull(root->right);
  }
};

int main(int argc, char *argv[]) {
  // some operations
  BinaryTree tree(1);

  assert(Solution().isPerfectRecursive(tree.root).second == 1);

  tree.add({2}, {'L'});
  assert(Solution().isPerfectRecursive(tree.root).second == 0);

  tree.add({3}, {'R'});
  assert(Solution().isPerfectRecursive(tree.root).second == 1);

  tree.add({3, 6}, {'R', 'R'});
  tree.add({3, 14}, {'R', 'L'});
  assert(Solution().isPerfectRecursive(tree.root).second == 0);

  tree.add({2, 4, 7}, {'L', 'L', 'L'});
  tree.add({2, 4, 8}, {'L', 'L', 'R'});
  tree.add({2, 5, 9}, {'L', 'R', 'R'});
  tree.add({3, 6, 15}, {'R', 'R', 'L'});
  assert(Solution().isPerfectRecursive(tree.root).second == 0);

  tree.add({2, 5, 13}, {'L', 'R', 'L'});
  tree.add({3, 6, 12}, {'R', 'R', 'R'});
  assert(Solution().isPerfectRecursive(tree.root).second == 0);

  tree.add({3, 14, 15}, {'R', 'L', 'L'});
  tree.add({3, 14, 16}, {'R', 'L', 'R'});

  assert(Solution().isPerfectRecursive(tree.root).second ==
         1); // now 8 leaf nodes

  std::cout << "bye";

  tree.clear();

  return 0;
}

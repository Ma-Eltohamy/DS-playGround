#include <assert.h>
#include <iostream>
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
  int maxDepth(TreeNode *cur) {
    if (!cur)
      return -1;

    int leftMax{std::max(cur->val, maxDepth(cur->left))};
    int rightMax{std::max(cur->val, maxDepth(cur->right))};

    return std::max(leftMax, rightMax);
  }
};

int main(int argc, char *argv[]) {
  // some operations

  BinaryTree tree(3);
  tree.add({9}, {'L'});
  tree.add({20, 15}, {'R', 'L'});
  tree.add({20, 7}, {'R', 'R'});
  // tree.add({2, 4, 7}, {'L', 'L', 'L'});
  // tree.add({2, 4, 8}, {'L', 'L', 'R'});
  // tree.add({2, 5, 9}, {'L', 'R', 'R'});
  // tree.add({3, 6, 10}, {'R', 'R', 'L'});

  std::cout << Solution().maxDepth(tree.root) << "\n";
  tree.clear();

  return 0;
}
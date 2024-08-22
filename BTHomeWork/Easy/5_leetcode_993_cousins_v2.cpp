#include <assert.h>
#include <iostream>
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
  // Parent Value && Child Depth
  std::pair<int, int> nodeDepthWithParent(TreeNode *root, int x) {
    if (!root)
      return std::make_pair(-1, -1);

    std::pair<int, int> targetInfo{std::make_pair(-1, -1)};

    if ((root->left && root->left->val == x) ||
        (root->right && root->right->val == x))
      return targetInfo = std::make_pair(root->val, 1);

    targetInfo = nodeDepthWithParent(root->left, x);
    if (targetInfo.second > -1) {
      ++targetInfo.second;
      return targetInfo;
    }

    targetInfo = nodeDepthWithParent(root->right, x);
    if (targetInfo.second > -1)
      ++targetInfo.second;
    return targetInfo;
  }
  bool isCousins(TreeNode *root, int x, int y) {
    std::pair<int, int> XInfo{nodeDepthWithParent(root, x)};
    std::pair<int, int> YInfo{nodeDepthWithParent(root, y)};

    // they don't have the same father
    // and
    // they're not on the same level or depth
    // then they're cousins
    if (XInfo.first != YInfo.first && XInfo.second == YInfo.second)
      return true;
    return false;
  }
};

int main(int argc, char *argv[]) {
  // some operations

  BinaryTree tree(1);
  tree.add({2, 4, 7}, {'L', 'L', 'L'});
  tree.add({2, 4, 8}, {'L', 'L', 'R'});
  tree.add({2, 5, 9}, {'L', 'R', 'R'});
  tree.add({3, 6, 10}, {'R', 'R', 'L'});

  std::cout << Solution().isCousins(tree.root, 7, 8) << "\n"; // 0

  tree.clear();

  return 0;
}

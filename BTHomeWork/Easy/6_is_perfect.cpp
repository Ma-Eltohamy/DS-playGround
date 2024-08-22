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
  // 0, -1
  // nodesNumber, maxDepth
  std::pair<int, int> TotalNodesMaxDepth(TreeNode *root) {
    if (!root)
      return std::make_pair(0, -1);

    std::pair<int, int> leftSubTreeInfo{TotalNodesMaxDepth(root->left)};
    std::pair<int, int> rightSubTreeInfo{TotalNodesMaxDepth(root->right)};

    std::pair<int, int> treeInfo{
        (leftSubTreeInfo.first + rightSubTreeInfo.first + 1),
        (std::max(leftSubTreeInfo.second, rightSubTreeInfo.second) + 1)};
    return treeInfo;
  }

  bool isPerfectFormula(TreeNode *root) {
    // nodesNumber, maxDepth
    int actualTotalNodes{}, maxDepth{};
    std::tie(actualTotalNodes, maxDepth) = TotalNodesMaxDepth(root);
    int expectedTotalNodes = std::pow(2, maxDepth + 1) - 1;
    return actualTotalNodes == expectedTotalNodes;
  };

  // recursive
  std::pair<int, bool>
  isPerfectRecursive(TreeNode *root) { // O(n) time O(n) memory
    if (!root)
      return std::make_pair(-1, true);

    std::pair<int, bool> leftSubTreeInfo{isPerfectRecursive(root->left)};
    if (!leftSubTreeInfo.second)
      return std::make_pair(-1, false);
    std::pair<int, bool> rightSubTreeInfo{isPerfectRecursive(root->right)};
    if (!rightSubTreeInfo.second)
      return std::make_pair(-1, false);

    if (leftSubTreeInfo.first != rightSubTreeInfo.first)
      return std::make_pair(-1, false);

    return std::make_pair(leftSubTreeInfo.first + 1, true);
  };
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

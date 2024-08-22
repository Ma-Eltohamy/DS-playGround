#include <algorithm>
#include <assert.h>
#include <iostream>
#include <queue>
#include <string>
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
  std::vector<std::vector<int>> levelOrder(TreeNode *root) {
    std::vector<std::vector<int>> res;

    if (!root)
      return res;

    std::queue<TreeNode *> q;
    q.push(root);
    std::vector<int> levelRes;
    int qSize{(int)q.size()};
    TreeNode *cur{};

    while (!q.empty()) {
      qSize = (int)q.size();
      while (qSize--) {
        cur = q.front();
        q.pop();

        levelRes.push_back(cur->val);

        if (cur->left)
          q.push(cur->left);
        if (cur->right)
          q.push(cur->right);
      }
      res.push_back(levelRes);
    }
    std::reverse(res.begin(), res.end());
    return res;
  }
};

int main() {

  std::vector<std::string> leetCodeSerializedTree = {};

  std::cout << "\nbye\n";

  return 0;
}

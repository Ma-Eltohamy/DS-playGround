#include <assert.h>
#include <deque>
#include <iostream>
#include <queue>
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

  void printLevelOrder1() {
    std::queue<TreeNode *> q;
    q.push(root);

    TreeNode *cur{};
    while (!q.empty()) {
      cur = q.front();
      q.pop();
      std::cout << cur->val << ' ';

      if (cur->left)
        q.push(cur->left);

      if (cur->right)
        q.push(cur->right);
    }
    std::cout << '\n';
  }

  void printLevelOrder2() {
    std::queue<TreeNode *> q;
    q.push(root);

    TreeNode *cur{};
    int qSize{(int)q.size()};
    int level{0};
    while (!q.empty()) {
      qSize = (int)q.size();
      std::cout << "level " << level << ": ";
      ++level;
      while (qSize--) {
        cur = q.front();
        q.pop();
        std::cout << cur->val << ' ';

        if (cur->left)
          q.push(cur->left);
        if (cur->right)
          q.push(cur->right);
      }
      std::cout << '\n';
    }
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
  bool isCompleteTree(TreeNode *root) {
    if (!root)
      return false;

    std::queue<TreeNode *> q;
    int qSize{};
    bool allowChildren{true};
    TreeNode *cur{};

    q.push(root);
    while (!q.empty()) {
      qSize = (int)q.size();

      while (qSize--) {
        cur = q.front();
        q.pop();

        if ((cur->left || cur->right) && !allowChildren)
          return false;
        if (cur->left) {
          q.push(cur->left);
        } else
          allowChildren = false;
        if (cur->right) {
          q.push(cur->right);
        } else
          allowChildren = false;
      }
    }
    return true;
  }
};

int main() {

  BinaryTree tree(1);

  // left side
  tree.add({2, 5}, {'L', 'L'});
  // tree.add({2, 5}, {'L', 'R'});
  // right side
  tree.add({3, 7}, {'R', 'L'});
  tree.add({3, 8}, {'R', 'R'});
  tree.printLevelOrder2();
  std::cout << Solution().isCompleteTree(tree.root) << std::endl;
  std::cout << "bye\n";

  return 0;
}

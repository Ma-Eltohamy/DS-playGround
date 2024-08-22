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
TreeNode* invertTree(TreeNode* root) {
        if (!root)
            return nullptr;

        else {
            TreeNode* l = invertTree(root->left);
            TreeNode* r = invertTree(root->right);
            root->left = r;
            root->right = l;
            return root;
        }
    }
};

int main() {

  BinaryTree tree(4);

  // left side
  tree.add({7, 9}, {'L', 'L'});
  tree.add({7, 6}, {'L', 'R'});
  // right side
  tree.add({2, 1}, {'R', 'R'});
  tree.add({2, 3}, {'R', 'L'});
  tree.printLevelOrder2();
  std::cout << Solution().invertTree(tree.root) << std::endl;
  tree.printLevelOrder2();
  std::cout << "bye\n";

  return 0;
}

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
  std::vector<std::vector<int>> zigzagLevelOrder(TreeNode *root) {
    std::vector<std::vector<int>> res;
    if (!root)
      return res;

    std::deque<TreeNode *> deq;
    deq.push_back(root);

    bool isEven{false};
    int deqSize{(int)deq.size()};
    TreeNode *cur{};
    while (!deq.empty()) {
      std::vector<int> curLevelVal{};
      deqSize = (int)deq.size();
      while (deqSize--) {
        if (!isEven) {
          cur = deq.front();
          deq.pop_front();

          if (cur->left)
            deq.push_back(cur->left);
          if (cur->right)
            deq.push_back(cur->right);
        } else {
          cur = deq.back();
          deq.pop_back();

          if (cur->right)
            deq.push_front(cur->right);
          if (cur->left)
            deq.push_front(cur->left);
        }
        curLevelVal.push_back(cur->val);
      }
      isEven = !isEven;
      res.push_back(curLevelVal);
    }
    return res;
  }
};

void test1_level_order_traversal1() {
  BinaryTree tree(1);

  tree.add({2, 4, 8}, {'L', 'L', 'L'});
  tree.add({2, 4, 9}, {'L', 'L', 'R'});
  tree.add({2, 5, 10}, {'L', 'R', 'L'});
  tree.add({2, 5, 11}, {'L', 'R', 'R'});

  tree.add({3, 6, 12}, {'R', 'L', 'L'});
  tree.add({3, 6, 13}, {'R', 'L', 'R'});
  tree.add({3, 7, 14}, {'R', 'R', 'L'});
  tree.add({3, 7, 15}, {'R', 'R', 'R'});

  tree.printLevelOrder2();
  // Level 0: 1
  // Level 1: 2 3
  // Level 2: 4 5 6 7
  // Level 3: 8 9 10 11 12 13 14 15
  std::vector<std::vector<int>> vec{Solution().zigzagLevelOrder(tree.root)};

  for (auto v : vec) {
    for (auto num : v)
      std::cout << num << ' ';
    std::cout << '\n';
  }
}

int main() {
  test1_level_order_traversal1();

  std::cout << "bye\n";

  return 0;
}

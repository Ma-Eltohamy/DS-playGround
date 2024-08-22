#include <algorithm>
#include <assert.h>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

// Problem link
// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/

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

  void printLevelOrder2(TreeNode *root) {
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

private:
  void _clear(TreeNode *cur) {
    if (!cur)
      return;

    _clear(cur->left), _clear(cur->right);
    delete cur;
  }

public:
  void clear() {
    _clear(root);
    std::cout << "\nTree has been cleaned.\n";
  }

private:
  void _parenthazingTree(std::string &res, TreeNode *root) {
    res += "(" + std::to_string(root->val);
    if (root->left)
      _parenthazingTree(res, root->left);
    else
      res += "()";
    if (root->right)
      _parenthazingTree(res, root->right);
    else
      res += "()";
    res += ')';
  }

public:
  std::string parenthazingTree() {
    if (!root)
      return "";
    std::string res{};
    _parenthazingTree(res, root);
    return res;
  }

private:
  std::string _canoclize(TreeNode *root) {
    if (!root)
      return "()";

    std::string res = "(" + std::to_string(root->val);
    std::vector<std::string> v;

    if (root->left)
      v.push_back(_canoclize(root->left));
    else
      v.push_back("()");
    if (root->right)
      v.push_back(_canoclize(root->left));
    else
      v.push_back("()");

    std::sort(v.begin(), v.end());
    for (auto item : v)
      res += item;
    return res;
  }

public:
  std::string canoclize() { return _canoclize(root); }
};

class Solution {
public:
  bool _isSymmetric(TreeNode *leftRoot, TreeNode *rightRoot) {
    if (!leftRoot && !rightRoot)
      return true;
    if ((leftRoot && !rightRoot) || (!leftRoot && rightRoot) ||
        (leftRoot->val != rightRoot->val))
      return false;

    bool first{_isSymmetric(leftRoot->left, rightRoot->right)};
    bool second{_isSymmetric(leftRoot->right, rightRoot->left)};
    return first && second;
  }
  bool isSymmetric(TreeNode *root) {
    if (!root)
      return false;
    return _isSymmetric(root->left, root->right);
  }
};

int main() {

  BinaryTree tree(1);
  tree.add({2, 4, 7}, {'L', 'L', 'L'});
  tree.add({2, 4, 8}, {'L', 'L', 'R'});
  tree.add({2, 5, 9}, {'L', 'R', 'R'});
  tree.add({3, 6, 10}, {'R', 'R', 'L'});

  std::cout << Solution().isSymmetric(tree.root) << "\n";

  std::cout << "\nbye\n";

  return 0;
}

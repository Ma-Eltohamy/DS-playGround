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
  std::string _parenthasizeCanocal(TreeNode *root) {
    if (!root)
      return "()";

    std::string res = "(" + std::to_string(root->val);
    std::multiset<std::string> v;

    if (root->left)
      v.insert(_parenthasizeCanocal(root->left));
    else
      v.insert("()");
    if (root->right)
      v.insert(_parenthasizeCanocal(root->left));
    else
      v.insert("()");

    for (auto item : v)
      res += item;
    res += ')';
    return res;
  }

public:
  std::string parenthasizeCanocal() { return _parenthasizeCanocal(root); }
};

BinaryTree *leetCodeDeserializer(std::vector<std::string> &res) {
  if (res.empty() || res.front() == "null")
    return nullptr;

  int resSize = (int)res.size();
  std::queue<TreeNode *> q;
  BinaryTree *bt{new BinaryTree(new TreeNode(std::stoi(res[0])))};
  q.push(bt->root);
  TreeNode *cur{}, *leftChild{}, *rightChild{};
  int idx = 0;

  while (!q.empty()) {
    cur = q.front(), q.pop();

    leftChild = rightChild = nullptr;
    if (++idx < resSize && res[idx] != "null")
      leftChild = new TreeNode(std::stoi(res[idx]));
    if (++idx < resSize && res[idx] != "null")
      rightChild = new TreeNode(std::stoi(res[idx]));

    if (leftChild)
      q.push(leftChild), cur->left = leftChild;
    if (rightChild)
      q.push(rightChild), cur->right = rightChild;
  }
  return bt;
}

class Solution {
public:
  std::string &parenthasizeCanocal(TreeNode *root, std::string &res) {
    if (!root) {
      res += "()";
      return res;
    }
    res += '(' + std::to_string(root->val);
    if (root->left && root->right) {
      if (root->left->val >= root->right->val) {
        parenthasizeCanocal(root->right, res);
        parenthasizeCanocal(root->left, res);
      } else {
        parenthasizeCanocal(root->left, res);
        parenthasizeCanocal(root->right, res);
      }
    } else {
      res += "()";
      if (root->left)
        parenthasizeCanocal(root->left, res);
      else if (root->right)
        parenthasizeCanocal(root->right, res);
      else
        res += "()";
    }
    res += ')';
    return res;
  }
  bool flipEquiv(TreeNode *root1, TreeNode *root2) {
    std::string res1{}, res2{};
    return parenthasizeCanocal(root1, res1) == parenthasizeCanocal(root2, res2);
  }
};

int main() {
  std::vector<std::string> firstTree{"1",    "2",    "3",    "4", "5", "6",
                                     "null", "null", "null", "7", "8"};
  std::vector<std::string> secondTree{"1",    "2",    "3",    "4", "5", "6",
                                      "null", "null", "null", "7", "8"};
  BinaryTree *bt1{leetCodeDeserializer(firstTree)};
  BinaryTree *bt2{leetCodeDeserializer(secondTree)};

  std::string res1{}, res2{};
  std::cout << Solution().parenthasizeCanocal(bt1->root, res1) << std::endl;
  std::cout << Solution().parenthasizeCanocal(bt2->root, res2) << std::endl;
  std::cout << "\n\nbye\n";

  return 0;
}

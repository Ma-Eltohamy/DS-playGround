#include <assert.h>
#include <iostream>
#include <queue>
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
///////////////////////// Level Deserializing Null //////////////////////////
///
///////////////////////// Could be used with leetCode////////////////////////
BinaryTree *leetCodeDeserializer(std::vector<std::string> &res) {
  if (res.empty() || res.front() == "null")
    return new BinaryTree(nullptr);

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
void printInorder(TreeNode *current) {
  if (!current)
    return;
  printInorder(current->left);
  std::cout << current->val << " ";
  printInorder(current->right);
}

class Solution {
public:
  void parenthazingTree(std::string &res, TreeNode *root) {
    res += "(" + std::to_string(root->val);
    if (root->left)
      parenthazingTree(res, root->left);
    else
      res += "()";
    if (root->right)
      parenthazingTree(res, root->right);
    else
      res += "()";
    res += ')';
  }
  std::string serialize(TreeNode *root) {
    if (!root)
      return "";
    std::string res{};
    parenthazingTree(res, root);
    return res;
  }

  TreeNode *_deserialize(std::string &data, std::string &curVal, int &idx) {
    if (idx >= data.size() || data[idx] == ')') {
      ++idx;
      return nullptr;
    }

    while (data[idx] != '(' && data[idx] != ')') {
      curVal += data[idx];
      ++idx;
    }
    int val = std::stoi(curVal);
    TreeNode *root = new TreeNode(val);

    curVal.clear();
    if (idx < data.size() && data[idx] == '(')
      root->left = _deserialize(data, curVal, ++idx);

    if (idx < data.size() && data[idx] == '(')
      root->right = _deserialize(data, curVal, ++idx);

    ++idx;
    return root;
  }
  TreeNode *deserialize(std::string data) {
    if (data.empty())
      return nullptr;

    std::string curVal{};
    int idx{1};
    return _deserialize(data, curVal, idx);
  }
};

int main() {

  // std::vector<std::string> leetCodeSerializedTree = {
  //     "4",    "-7", "-3",   "null", "null", "-9", "-3",   "9",
  //     "-7",   "-4", "null", "6",    "null", "-6", "-6",   "null",
  //     "null", "0",  "6",    "5",    "null", "9",  "null", "null",
  //     "-1",   "-4", "null", "null", "null", "-2"};
  std::vector<std::string> leetCodeSerializedTree = {"1", "2", "3"};

  BinaryTree *bt{leetCodeDeserializer(leetCodeSerializedTree)};
  std::string parenthasizedBT{Solution().serialize(bt->root)};
  std::cout << parenthasizedBT << std::endl;
  TreeNode *root{Solution().deserialize(parenthasizedBT)};
  printInorder(root);

  std::cout << "\nbye\n";

  return 0;
}

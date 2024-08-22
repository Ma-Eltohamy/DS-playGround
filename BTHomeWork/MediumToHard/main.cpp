#include <algorithm>
#include <assert.h>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <utility>
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
  //   std::vector<TreeNode *> findDuplicateSubtrees(TreeNode *root) {}

  std::string
  _parenthazingTree(std::vector<std::tuple<std::string, int, TreeNode *>> &repr,
                    TreeNode *root) { // O(n^2) time
    std::string res = "(" + std::to_string(root->val);
    if (root->left)
      res += _parenthazingTree(repr, root->left);
    else
      res += "()";
    if (root->right)
      res += _parenthazingTree(repr, root->right);
    else
      res += "()";
    res += ')';

    bool isFound{false};
    for (auto &item : repr) {
      if (std::get<0>(item) == res) {
        ++std::get<1>(item), isFound = true;
        break;
      }
    }
    if (!isFound)
      repr.push_back(std::make_tuple(res, 0, root));
    return res;
  }

  // void printAllDuplicateSubTrees(TreeNode *root) {
  //   std::vector<std::pair<std::string, std::pair<int, TreeNode *>>> repr{};
  //
  //   _parenthazingTree(repr, root);
  //
  //   for (auto &item : repr)
  //     if (item.second.first)
  //       std::cout << item.first << std::endl;
  // }

  std::vector<TreeNode *> findDuplicateSubtrees(TreeNode *root) {
    std::vector<TreeNode *> res;
    std::vector<std::tuple<std::string, int, TreeNode *>> repr{};
    _parenthazingTree(repr, root); // O(n^2) time
    for (auto &item : repr)        // O(n) time
      if (std::get<1>(item))
        res.push_back(std::get<2>(item));
    return res;
  }

  TreeNode *_buildTree(std::vector<int> &inorder, std::vector<int> &postorder,
                       int start, int end) {
    if (end < start || postorder.empty())
      return nullptr;

    int val{postorder[(int)postorder.size() - 1]};
    postorder.erase(postorder.end());
    auto it = std::find(inorder.begin(), inorder.end(), val);
    int curIdx = it - inorder.begin();

    TreeNode *root{new TreeNode(val)};

    root->right = _buildTree(inorder, postorder, curIdx + 1, end);
    root->left = _buildTree(inorder, postorder, start, curIdx - 1);

    return root;
  }
  TreeNode *buildTree(std::vector<int> &inorder, std::vector<int> &postorder) {
    if (inorder.empty() || postorder.empty())
      return nullptr;
    return _buildTree(inorder, postorder, 0, (int)inorder.size() - 1);
  }
};

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
int main() {
  // std::vector<std::string> binaryTree{
  //     "1", "2",    "4",    "3",    "null", "2",    "5",    "null", "null",
  //     "3", "null", "6",    "6",    "null", "null", "7",    "8",    "7",
  //     "8", "null", "null", "null", "8",    "null", "null", "null", "8"};
  // BinaryTree *bt1{leetCodeDeserializer(binaryTree)};
  // bt1->printLevelOrder2(bt1->root);
  // std::vector<TreeNode *> v{Solution().findDuplicateSubtrees(bt1->root)};
  // for (auto item : v)
  //   std::cout << item->val << std::endl;
  //   /////////
  std::vector<int> inorder{9, 3, 15, 20, 7};
  std::vector<int> postorder{9, 15, 7, 20, 3};
  printLevelOrder2(Solution().buildTree(inorder, postorder));

  std::cout << std::endl;

  std::cout << "\n\nbye\n";

  return 0;
}

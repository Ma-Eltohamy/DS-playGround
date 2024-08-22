#include <algorithm>
#include <assert.h>
#include <iostream>
#include <queue>
#include <string>
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
///////////////////////// Level Deserializing Null //////////////////////////
///
///////////////////////// Could be used with leetCode////////////////////////
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
  TreeNode *_buildTree(std::vector<int> &preorder, std::vector<int> &inorder,
                       int start, int end) {
    if (end < start || preorder.empty())
      return nullptr;

    int val{preorder[0]};
    preorder.erase(preorder.begin());

    auto it = std::find(inorder.begin(), inorder.end(), val);
    int curIdx = it - inorder.begin();

    TreeNode *root{new TreeNode(val)};

    root->left = _buildTree(preorder, inorder, start, curIdx - 1);
    root->right = _buildTree(preorder, inorder, curIdx + 1, end);

    return root;
  }
  TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
    if (preorder.empty() || inorder.empty())
      return nullptr;
    return _buildTree(preorder, inorder, 0, inorder.size() - 1);
  }
};

int main() {

  std::vector<std::string> leetCodeSerializedTree = {};

  std::cout << "\nbye\n";

  return 0;
}

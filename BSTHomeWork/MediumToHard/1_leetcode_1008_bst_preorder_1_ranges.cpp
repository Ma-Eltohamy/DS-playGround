#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct TreeNode {
  int val{};
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(int val) : val(val) {}
};

struct BinaryTree {
  TreeNode *root{};
  BinaryTree(int root_value) : root(new TreeNode(root_value)) {}

  void add(vector<int> values, vector<char> direction) {
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

  void _print_inorder(TreeNode *current) {
    if (!current)
      return;
    _print_inorder(current->left);
    cout << current->val << " ";
    _print_inorder(current->right);
  }

  void print_inorder() {
    _print_inorder(root);
    cout << "\n";
  }
};
void _print_inorder(TreeNode *current) {
  if (!current)
    return;
  _print_inorder(current->left);
  cout << current->val << " ";
  _print_inorder(current->right);
}

TreeNode *leetCodeDeserializer(std::vector<std::string> &res) {
  if (res.empty() || res.front() == "null")
    return nullptr;

  int resSize = (int)res.size();
  std::queue<TreeNode *> q;
  TreeNode *root{new TreeNode(std::stoi(res[0]))};
  q.push(root);
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
  return root;
}
class Solution {
public:
  TreeNode *_bstFromPreorder(std::vector<int> &preorder, long long int max,
                             long long int min) {

    TreeNode *cur{new TreeNode(preorder[0])};
    preorder.erase(preorder.begin());

    if (!preorder.empty()) {
      if (min < preorder[0] && preorder[0] < cur->val)
        cur->left = _bstFromPreorder(preorder, cur->val, min);
      if (cur->val < preorder[0] && preorder[0] < max)
        cur->right = _bstFromPreorder(preorder, max, cur->val);
    }
    return cur;
  }
  TreeNode *bstFromPreorder(vector<int> &preorder) {
    if (preorder.empty())
      return nullptr;
    return _bstFromPreorder(preorder, LLONG_MAX, LLONG_MIN);
  }
};

int main() {
  std::vector<std::string> v{"0", "-2", "null", "-3", "null", "null", "null"};
  TreeNode *root{leetCodeDeserializer(v)};
  _print_inorder(root);
  std::cout << "\n";

  return 0;
}

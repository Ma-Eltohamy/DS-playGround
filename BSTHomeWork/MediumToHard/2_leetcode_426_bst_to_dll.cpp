#include <cassert>
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
  void link(TreeNode *first, TreeNode *second) {
    if (first)
      first->right = second;
    if (second)
      second->left = first;
  }

  std::pair<TreeNode *, TreeNode *> _bstToSortedDLL(TreeNode *root) {
    if (!root->left && !root->right)
      return std::make_pair(root, root);

    std::pair<TreeNode *, TreeNode *> leftChain{root, root},
        rightChain{root, root};

    if (root->left) {
      leftChain = _bstToSortedDLL(root->left);
      link(leftChain.second, root);
    }

    if (root->right) {
      rightChain = _bstToSortedDLL(root->right);
      link(root, rightChain.first);
    }

    return std::make_pair(leftChain.first, rightChain.second);
  }

  TreeNode *bstToSortedDLL(TreeNode *root) {
    if (!root)
      return nullptr;
    std::pair<TreeNode *, TreeNode *> DLL{_bstToSortedDLL(root)};

    return DLL.first;
  }
};

int main() {
  std::vector<std::string> v{"0", "-2", "null", "-3", "null", "null", "null"};
  TreeNode *root{leetCodeDeserializer(v)};
  _print_inorder(root);
  std::cout << "\n";
  std::cout << Solution().bstToSortedDLL(root)->val << std::endl;

  return 0;
}

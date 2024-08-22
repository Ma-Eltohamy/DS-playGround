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
  BinaryTree() {}
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

  void _printLevelOrder2(TreeNode *root) {
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
  void printLevelOrder2() { _printLevelOrder2(root); }

  void constructBinaryHeap(std::vector<int> &completeBT) {
    if ((int)completeBT.size() == 0 || root)
      return;
    int i{0}, completeBTSize{(int)completeBT.size()};

    root = new TreeNode(completeBT[i++]);
    std::queue<TreeNode *> q;
    q.push(root);
    TreeNode *cur{}, *left{}, *right{};

    while (!q.empty()) {
      cur = q.front();
      q.pop();

      if (i < completeBTSize) {
        left = new TreeNode(completeBT[i++]);
        cur->left = left;
        q.push(left);
      }
      if (i < completeBTSize) {
        right = new TreeNode(completeBT[i++]);
        cur->right = right;
        q.push(right);
      }
    }
  }

  void toVec(std::vector<int> &HeapVec) {
    if (!root)
      return;

    std::queue<TreeNode *> q;
    q.push(root);
    TreeNode *cur{};

    while (!q.empty()) {
      cur = q.front();
      q.pop();
      HeapVec.push_back(cur->val);

      if (cur->left)
        q.push(cur->left);

      if (cur->right)
        q.push(cur->right);
    }
  }
};

int main() {
  // Construct min Binary Heap from vector
  std::vector<int> completeBT{2, 6, 8, 14, 7, 10, 19, 37, 25, 30, 12, 22, 17};
  BinaryTree bt;
  bt.constructBinaryHeap(completeBT);
  bt.printLevelOrder2();
  //
  // Construct Vector of min Binary Heap
  std::vector<int> HeapVec{};
  bt.toVec(HeapVec);

  int heapSize{(int)HeapVec.size()};
  for (int i = 0; i < heapSize; ++i)
    std::cout << HeapVec[i] << ' ';
  std::cout << std::endl;

  cout << "bye\n";
  return 0;
}

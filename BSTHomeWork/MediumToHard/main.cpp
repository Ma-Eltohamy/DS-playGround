#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct TreeNode {
  int val{};
  TreeNode *left{};
  TreeNode *right{};
  TreeNode *parent{};
  TreeNode(int val) : val(val) {}
};

struct BinaryTree {
  TreeNode *root{};
  BinaryTree() {}
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

  void _print_inorder(TreeNode *current) {
    if (!current)
      return;
    _print_inorder(current->left);
    std::cout << current->val << " ";
    _print_inorder(current->right);
  }

  void print_inorder() {
    _print_inorder(root);
    std::cout << "\n";
  }

  TreeNode *_min(TreeNode *root) {
    while (root && root->left)
      root = root->left;
    return root;
  }
  int min() { return _min(root)->val; }

  int _max(TreeNode *root) {
    while (root && root->right)
      root = root->right;
    return root->val;
  }

  int max() { return _max(root); }

  void _insert(TreeNode *&root, TreeNode *parent, int val) {
    if (!root) {
      root = new TreeNode(val);
      root->parent = parent;
      return;
    }

    if (val < root->val)
      _insert(root->left, root, val);
    else
      _insert(root->right, root, val);
  }

  void insert(int val) {
    if (!root)
      root = new TreeNode(val);
    else
      _insert(root, nullptr, val);
  }

  void printWithParent(TreeNode *root) {
    if (!root)
      return;

    std::cout << "ParentNode is: ";
    if (root->parent)
      std::cout << root->parent->val;
    else
      std::cout << "nullptr";
    std::cout << " cur node value: " << root->val << std::endl;

    if (root->left) {
      std::cout << "on l ";
      printWithParent(root->left);
    }
    if (root->right) {
      std::cout << "on r";
      printWithParent(root->right);
    }
  }

  bool findChain(int target, std::vector<TreeNode *> &anscestors) {
    TreeNode *cur{root};
    bool isFound{false};

    while (cur && !isFound) {
      if (target > cur->val)
        cur = cur->right;
      else {
        anscestors.push_back(cur);
        if (target == cur->val)
          isFound = true;
        else
          cur = cur->left;
      }
    }
    return isFound;
  }

  TreeNode *getNext(std::vector<TreeNode *> &anscestors) {
    if (anscestors.empty())
      return nullptr;
    TreeNode *cur{anscestors.back()};
    anscestors.pop_back();
    return cur;
  }

  std::pair<bool, int> successor(int val) {
    std::vector<TreeNode *> anscestors;
    if (!findChain(val, anscestors))
      return std::make_pair(false, -1);

    TreeNode *child{getNext(anscestors)};
    if (child->right)
      return std::make_pair(true, _min(child->right)->val);

    TreeNode *parent{getNext(anscestors)};

    if (parent)
      return std::make_pair(true, parent->val);
    return std::make_pair(false, -1);
  }

  bool preFindChain(int target, std::vector<TreeNode *> &ancestors) {
    TreeNode *cur{root};
    bool isFound{false};

    while (!isFound && cur) {
      if (target < cur->val)
        cur = cur->left;
      else {
        ancestors.push_back(cur);
        if (target == cur->val)
          isFound = true;
        else
          cur = cur->right;
      }
    }
    return isFound;
  }
  std::pair<bool, int> predecessor(int val) {
    std::vector<TreeNode *> ancestors;

    if (!preFindChain(val, ancestors)) // not found
      return std::make_pair(false, -1);

    TreeNode *child{getNext(ancestors)};
    if (child->left)
      return std::make_pair(true, _max(child->left));

    TreeNode *parent{getNext(ancestors)};
    if (parent)
      return std::make_pair(true, parent->val);
    return std::make_pair(false, -1);
  }

  TreeNode *deserialize(std::string data) {
    int dataLen{(int)data.length()};
    if (dataLen == 0)
      return nullptr;

    std::string num{};
    TreeNode *root{};
    for (int i = 0; i < dataLen; ++i) {
      if (data[i] == ',') {
        insert(std::stoi(num));
        num = "";
        continue;
      }
      num += data[i];
    }
    return root;
  }

  TreeNode *_deleteNode(TreeNode *root, int target) {
    if (!root)
      return nullptr;

    if (target > root->val)
      root->right = _deleteNode(root->right, target);
    else if (target < root->val)
      root->left = _deleteNode(root->left, target);
    else {
      TreeNode *tmp{root};
      // leaf target
      if (!root->left && !root->right)
        root = nullptr;
      else if (!root->left) // Only has right
        root = root->right;
      else if (!root->right) // Only has left
        root = root->left;
      else { // Has two childre
        // Get parent successor
        // Call _deleteNode(parentSuc, suc->val);
        TreeNode *parentSuc{root}, *successor{root->right};

        while (successor && successor->left)
          parentSuc = successor, successor = successor->left;

        root->val = successor->val; // copy & go delete
        root->right = _deleteNode(root->right, root->val);
        tmp = nullptr; // Don't delete me. Successor will be deleted
        //   if (parentSuc == root)
        //     successor->left = root->left;
        //
        //   else { // Then successor must be on my left as a parent
        //     if (!successor->left && !successor->right)
        //       parentSuc->left = nullptr;
        //     else
        //       parentSuc->left = successor->right;
        //     successor->left = root->left, successor->right = root->right;
        //   }
        //   root = successor;
      }
      if (tmp)
        delete tmp, tmp = nullptr;
    }
    return root;
  }

  void deleteNode(int target) { root = _deleteNode(root, target); }

  void _get_inorder(TreeNode *current, std::vector<int> &values) {
    if (!current)
      return;
    _get_inorder(current->left, values);
    values.push_back(current->val);
    _get_inorder(current->right, values);
  }

  std::vector<int> get_inorder() {
    std::vector<int> values;
    _get_inorder(root, values);
    return values;
  }
};
class Solution {
public:
  void _recoverTree(TreeNode *root, TreeNode *mis, long long min,
                    long long max) {
    if (mis)
      return;

    if (root->val > min && root->val < max) {
      if (root->left)
        _recoverTree(root, mis, min, root->val);
      if (root->right)
        _recoverTree(root, mis, root->val, max);
    } else {
      mis = root;
      return;
    }

    if (mis && mis->val > min && mis->val < max) {
      int tmp = mis->val;
      mis->val = root->val;
      root->val = tmp;
    }
  }
  void recoverTree(TreeNode *root) {
    if (!root)
      return;
    _recoverTree(root, nullptr, LONG_LONG_MIN, LONG_LONG_MAX);
  }
};

int main() {
  TreeNode *first{new TreeNode(1)};
  TreeNode *second{new TreeNode(3)};
  TreeNode *third{new TreeNode(2)};

  first->left = second;
  second->right = third;
  BinaryTree bt;
  bt.root = first;
  bt.print_inorder();
  Solution().recoverTree(bt.root);

  std::cout << "\nBye\n";

  return 0;
}

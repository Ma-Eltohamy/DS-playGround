#include <iostream>
#include <queue>

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

private:
  void _printInorder(TreeNode *current) {
    if (!current)
      return;
    _printInorder(current->left);
    std::cout << current->val << " ";
    _printInorder(current->right);
  }

  void _clear(TreeNode *cur) {
    if (!cur)
      return;

    _clear(cur->left), _clear(cur->right);
    delete cur;
  }

public:
  ////////////////////////////////
  /// Print Functions
  ////////////////////////////////
  void printInorder() {
    _printInorder(root);
    std::cout << "\n";
  }

  void printLevelOrderV2(TreeNode *root) {
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

  ////////////////////////////////
  /// Serializing with -1 functions
  ////////////////////////////////
  void preOrder_1Serialize(TreeNode *root, std::vector<int> &res) {
    res.push_back(root->val);
    if (root->left)
      preOrder_1Serialize(root->left, res);
    else {
      res.push_back(-1);
    }
    if (root->right)
      preOrder_1Serialize(root->right, res);
    else {
      res.push_back(-1);
    }
  }

  void postOrder_1Serialize(TreeNode *root, std::vector<int> &res) {
    if (root->left)
      postOrder_1Serialize(root->left, res);
    else {
      res.push_back(-1);
    }
    if (root->right)
      postOrder_1Serialize(root->right, res);
    else {
      res.push_back(-1);
    }
    res.push_back(root->val);
  }

  void levelOrder_1Serialize(TreeNode *root, std::vector<int> &res) {
    std::queue<TreeNode *> q;
    q.push(root);
    res.push_back(root->val);

    TreeNode *cur{};
    while (!q.empty()) {
      cur = q.front();
      q.pop();

      if (cur->left)
        res.push_back(cur->left->val), q.push(cur->left);
      else
        res.push_back(-1);
      if (cur->right)
        res.push_back(cur->right->val), q.push(cur->right);
      else
        res.push_back(-1);
    }
  }

  ////////////////////////////////
  /// Serializing with null functions
  ////////////////////////////////
  void levelOrderNullSerialize(TreeNode *root, std::vector<std::string> &res) {
    std::queue<TreeNode *> q;
    q.push(root);
    res.push_back(std::to_string(root->val));

    TreeNode *cur{};
    while (!q.empty()) {
      cur = q.front();
      q.pop();

      if (cur->left)
        res.push_back(std::to_string(cur->left->val)), q.push(cur->left);
      else
        res.push_back("null");
      if (cur->right)
        res.push_back(std::to_string(cur->right->val)), q.push(cur->right);
      else
        res.push_back("null");
    }
  }

  void clear() {
    _clear(root);
    std::cout << "\nTree has been cleaned.\n";
  }
};
class Solution {
public:
  ///////////////////////////// Pre Deserializing //////////////////////////////
  TreeNode *DeserializedTreePreOrder_1(std::vector<int> &res, int &idx) {
    if (idx == (int)res.size() - 1 || res[idx] == -1)
      return nullptr;

    TreeNode *root{new TreeNode(res[idx])};

    root->left = DeserializedTreePreOrder_1(res, ++idx);
    root->right = DeserializedTreePreOrder_1(res, ++idx);
    return root;
  }

  ///////////////////////////// Post Deserializing /////////////////////////////
  TreeNode *DeserializedTreePostOrder_1(std::vector<int> &res, int &idx) {
    if (idx <= 0 || res[idx] == -1)
      return nullptr;

    TreeNode *root{new TreeNode(res[idx])};

    root->right = DeserializedTreePostOrder_1(res, --idx);
    root->left = DeserializedTreePostOrder_1(res, --idx);
    return root;
  }

  ////////////////////////// Level Deserializing -1 ////////////////////////////
private:
  TreeNode *_DeserializedTreeLevelOrder_1(std::vector<int> &res, int idx = 0) {
    if (idx >= (int)res.size() || res[idx] == -1)
      return nullptr;

    TreeNode *root{new TreeNode(res[idx])};

    idx *= 2;
    root->left = _DeserializedTreeLevelOrder_1(res, idx + 1);
    root->right = _DeserializedTreeLevelOrder_1(res, idx + 2);
    return root;
  }

public:
  TreeNode *DeserializedTreeLevelOrder_1(std::vector<int> &res) {
    return _DeserializedTreeLevelOrder_1(res);
  }

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
};

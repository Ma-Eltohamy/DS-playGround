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

  void printLevelOrder1() {
    std::queue<TreeNode *> q;
    q.push(root);

    TreeNode *cur{};
    while (!q.empty()) {
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
  TreeNode *DeserializedTreeLevelOrderNull(std::vector<std::string> &res) {
    if (res.empty() || res.front() == "null")
      return nullptr;

    int resSize = (int)res.size();
    std::queue<TreeNode *> q;
    TreeNode *root{new TreeNode(std::stoi(res[0]))};
    q.push(root);
    TreeNode *cur{}, *leftChild{}, *rightChild{};
    int idx = 0;

    while (!q.empty() && idx < resSize) {
      cur = q.front(), q.pop();

      leftChild = rightChild = nullptr;
      if (res[++idx] != "null")
        leftChild = new TreeNode(std::stoi(res[idx]));
      if (res[++idx] != "null")
        rightChild = new TreeNode(std::stoi(res[idx]));

      if (leftChild)
        q.push(leftChild), cur->left = leftChild;
      if (rightChild)
        q.push(rightChild), cur->right = rightChild;
    }
    return root;
  }
};

int main() {

  BinaryTree tree(4);

  std::vector<std::string> serializedTree;
  // // left side
  tree.add({-7}, {'L'});
  //  right side
  tree.add({-3, -3}, {'R', 'R'});
  tree.add({-3, -3, -4}, {'R', 'R', 'L'});
  tree.add({-3, -9, 9, 6, 0}, {'R', 'L', 'L', 'L', 'L'});
  tree.add({-3, -9, 9, 6, 0, -1}, {'R', 'L', 'L', 'L', 'L', 'R'});
  tree.add({-3, -9, 9, 6, 6}, {'R', 'L', 'L', 'L', 'R'});
  tree.add({-3, -9, 9, 6, 6, -4}, {'R', 'L', 'L', 'L', 'R', 'L'});
  tree.add({-3, -9, -7, -6}, {'R', 'L', 'R', 'R'});
  tree.add({-3, -9, -7, -6, 9, -2}, {'R', 'L', 'R', 'R', 'L', 'L'});
  tree.add({-3, -9, -7, -6, 5}, {'R', 'L', 'R', 'L', 'L'});

  tree.levelOrderNullSerialize(tree.root, serializedTree);
  std::cout << "\nSerialized Tree: ";
  for (auto item : serializedTree)
    std::cout << item << ' ';
  std::cout << '\n';

  // int idx{0};
  // serializedTree = {"3", "9", "20", "null", "null", "15", "7"};
  std::vector<std::string> serializedTree2 = {
      "4",    "-7", "-3",   "null", "null", "-9", "-3",   "9",
      "-7",   "-4", "null", "6",    "null", "-6", "-6",   "null",
      "null", "0",  "6",    "5",    "null", "9",  "null", "null",
      "-1",   "-4", "null", "null", "null", "-2"};
  // if (serializedTree == serializedTree2)
  //   std::cout << "yes\n";
  TreeNode *root{Solution().DeserializedTreeLevelOrderNull(serializedTree)};

  std::cout << "\nDeserialized Tree\n";
  tree.printLevelOrder2(root);
  std::cout << "\nbye\n";

  return 0;
}

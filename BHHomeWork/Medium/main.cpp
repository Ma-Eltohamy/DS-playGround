#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class BinaryTree {
private:
  int data{};
  BinaryTree *left{};
  BinaryTree *right{};

public:
  BinaryTree(int data) : data(data) {}

  void add(vector<int> values, vector<char> direction) {
    assert(values.size() == direction.size());
    BinaryTree *current = this;
    // iterate on the path, create all necessary nodes
    for (int i = 0; i < (int)values.size(); ++i) {
      if (direction[i] == 'L') {
        if (!current->left)
          current->left = new BinaryTree(values[i]);
        else
          assert(current->left->data == values[i]);
        current = current->left;
      } else {
        if (!current->right)
          current->right = new BinaryTree(values[i]);
        else
          assert(current->right->data == values[i]);
        current = current->right;
      }
    }
  }
  ////////////////////////////////////////////

  void level_order_traversal() {
    queue<BinaryTree *> nodes_queue;
    nodes_queue.push(this);

    while (!nodes_queue.empty()) {
      int sz = nodes_queue.size();

      while (sz--) {
        BinaryTree *cur = nodes_queue.front();
        nodes_queue.pop();

        cout << cur->data << " ";
        if (cur->left)
          nodes_queue.push(cur->left);
        if (cur->right)
          nodes_queue.push(cur->right);
      }
      cout << "\n";
    }
  }

  void level_order_traversal_sorted() {
    priority_queue<pair<int, BinaryTree *>> heaps[2];

    int flag = 0;
    heaps[flag].push(make_pair(data, this));

    while (!heaps[flag].empty()) {
      int sz = heaps[flag].size();

      while (sz--) {
        pair<int, BinaryTree *> cur_pair = heaps[flag].top();
        heaps[flag].pop();
        BinaryTree *cur = cur_pair.second;
        cout << cur_pair.first << " ";

        if (cur->left)
          heaps[!flag].push(make_pair(cur->left->data, cur->left));

        if (cur->right)
          heaps[!flag].push(make_pair(cur->right->data, cur->right));
      }
      cout << "\n";
      flag = !flag;
    }
  }
};

void test() {
  BinaryTree tree(1);

  tree.add({2, 4, 7}, {'L', 'L', 'L'});
  tree.add({2, 4, 8}, {'L', 'L', 'R'});
  tree.add({2, 5, 9}, {'L', 'R', 'R'});
  tree.add({3, 6, 15}, {'R', 'R', 'L'});

  tree.add({2, 5, 13}, {'L', 'R', 'L'});
  tree.add({3, 6, 12}, {'R', 'R', 'R'});
  tree.add({3, 14, 15}, {'R', 'L', 'L'});
  tree.add({3, 14, 16}, {'R', 'L', 'R'});

  tree.level_order_traversal();
  tree.level_order_traversal_sorted();
}

int main() {
  test();

  return 0;
}

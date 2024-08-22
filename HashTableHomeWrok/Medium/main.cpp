#include <algorithm>
#include <iostream>
#include <unordered_set>

struct Node {
  int data{};
  Node *next{};
  Node(int data) : data(data) {}
};
class LinkedList {
private:
  Node *head{};
  Node *tail{};
  int length{};

public:
  void print() {
    for (Node *cur{head}; cur; cur = cur->next)
      std::cout << cur->data << ' ';
    std::cout << '\n';
  }
  void insertEnd(int value) {
    Node *cur{new Node(value)};
    if (!head) {
      head = tail = cur;
      return;
    }

    tail->next = cur;
    tail = cur;
  }

  void createCycle() {
    for (int i = 0; i < 4; ++i)
      insertEnd(i);

    Node *now = tail;

    for (int i = 0; i < 3; ++i)
      insertEnd(14 + i);

    tail->next = now;
  }

  void removeCycle() {
    std::unordered_set<Node *> st;
    for (Node *cur{head}; cur; cur = cur->next) {
      if (st.count(cur->next))
        cur->next = nullptr;
      st.insert(cur);
    }
  }
};

int main(int argc, char *argv[]) {
  LinkedList lst;
  lst.createCycle();
  lst.removeCycle();
  lst.print();
  return 0;
}

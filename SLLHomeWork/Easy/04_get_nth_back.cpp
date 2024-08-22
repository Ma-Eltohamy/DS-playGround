#include <algorithm>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Node {
  int data;
  Node *next;
  Node(int data) : data(data) {}
  ~Node() {
    std::cout << "Destroy value: " << data << " at address " << this << '\n';
  }
};

class LinkedList {
private:
  Node *head{};
  Node *tail{};
  int listLen{};

  // for debuggin
  std::vector<Node *> debugData;

  // debuggin functions
  void debugAddNode(Node *node) { debugData.push_back(node); }
  void debugDeleteNode(Node *node) {
    auto it = std::find(debugData.begin(), debugData.end(), node);
    if (it != debugData.end()) { // found
      debugData.erase(it);
    } else
      std::cout << "No such node found.\n";
  }

  Node *debugIsSeparate(Node *node) const {
    if (!node)
      return nullptr;

    Node *prev{node};
    Node *cur{prev->next};

    while (cur)
      prev = cur, cur = cur->next;

    if (prev == tail)
      return nullptr;

    return prev; // so this is a whole borken chain
  }
  void debugNodeVisualizer(Node *node) const {
    if (!node) {
      std::cout << "nullptr\n";
      return;
    }

    if (debugIsSeparate(node))
      std::cout << "Sep: ";

    std::cout << node->data;

    if (node->next)
      std::cout << ' ' << node->next->data;
    else
      std::cout << " X";

    if (node == head)
      std::cout << " head";
    if (node == tail)
      std::cout << " tail";

    std::cout << std::endl;
  }

  LinkedList(const LinkedList &) = delete;
  LinkedList &operator=(const LinkedList &) const = delete;

public:
  LinkedList(){};

  // debuggin functions
  void debugIntegrityCheck() const {
    if (!head) {
      assert(head == nullptr);
      assert(tail == nullptr);
      return;
    }

    assert(head);
    assert(tail);

    if (head == tail) {
      assert(listLen == 1);
      return;
    }

    else if (head->next == tail) {
      assert(listLen == 2);
      return;
    }

    else if (head->next != tail) {
      assert(listLen > 2);

      int len{0};
      Node *prev{};
      for (Node *cur = head; cur; prev = cur, cur = cur->next)
        ++len;

      assert(prev == tail);
      assert(len == (int)debugData.size()); // make sure they're all connected
      assert(len == listLen);
    }

    assert(tail->next == nullptr);
  }

  void debugVisualizer() const {
    for (auto node : debugData)
      debugNodeVisualizer(node);
  }

  /////////// just for make bugs and testing ////////////
  Node *&getHead() { return head; }
  ///////////////////////////////////////////////////////

  // user functions
  void addNode(Node *node) {
    debugAddNode(node);
    ++listLen;
  }
  void deleteNode(Node *node) {
    debugDeleteNode(node);
    --listLen;
    delete node;
    node = nullptr;
  }

  std::string debugToStr() {
    if (listLen == 0)
      return "";
    std::stringstream oss;
    for (Node *cur = head; cur; cur = cur->next) {
      oss << cur->data;
      if (cur->next)
        oss << " ";
    }
    return oss.str();
  }
  // insertion functions
  void insertFront(int value) { // O(1) time O(1) memroy
    Node *cur{new Node(value)};
    addNode(cur);
    if (head)
      cur->next = head;
    else
      tail = cur;
    head = cur;
    debugIntegrityCheck();
  }

  void insertEnd(int value) { // O(1) time O(1) memroy
    Node *cur{new Node(value)};
    addNode(cur);
    if (tail)
      tail->next = cur;
    else
      head = cur;
    tail = cur;
    debugIntegrityCheck();
  }

  void print() const {
    std::cout << "\nprinted List: ";
    for (Node *cur = head; cur; cur = cur->next)
      std::cout << cur->data << ' ';
    std::cout << std::endl;
  }

  void deleteFront() { // O(1) time O(1) memeory
    if (!head)
      return;

    Node *tmp{head};

    if (head == tail)
      head = tail = nullptr;
    else
      head = head->next;
    deleteNode(tmp);
    debugIntegrityCheck();
  }

  Node *getNth(int pos) const {
    if (pos > 0 && head) {
      int cnt{0};
      for (Node *cur = head; cur; cur = cur->next)
        if (++cnt == pos)
          return cur;
    }
    return nullptr; // nullptr when empty list and not found
  }
  ///////////////////////////// new function /////////////////////////////
  Node *getNthBack(int pos) { // O(n) time O(1) memroy
    return getNth(listLen + 1 - pos);
  }
  ///////////////////////////// new function /////////////////////////////

  ~LinkedList() {
    for (auto node : debugData)
      delete node;
  }
};

void test1() {
  cout << "\n\ntest1\n";
  LinkedList list;

  list.insertEnd(1);
  assert(list.getNthBack(1)->data == 1);
  list.insertEnd(2);
  list.insertEnd(3);
  assert(list.getNthBack(1)->data == 3);
  assert(list.getNthBack(3)->data == 1);
}

int main() {
  test1();
  // test2();
  // test3();
  // test4();

  // must see it, otherwise RTE
  std::cout << "\n\nNO RTE\n";

  return 0;
}

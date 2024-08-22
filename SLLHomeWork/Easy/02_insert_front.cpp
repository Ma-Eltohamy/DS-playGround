#include <algorithm>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>

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
    }

    assert(head);
    assert(tail);

    if (head == tail)
      assert(listLen == 1);

    else if (head->next == tail)
      assert(listLen == 2);

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
  ///////////////////////////// new function /////////////////////////////
  void insertFront(int value) { // O(1) time O(1) memroy
    Node *cur{new Node(value)};
    addNode(cur);
    if (!head)
      tail = cur;
    else
      cur->next = head;
    head = cur;
    debugIntegrityCheck();
  }
  ///////////////////////////// new function /////////////////////////////

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

  ~LinkedList() {
    for (auto node : debugData)
      delete node;
  }
};

void test1() {
  std::cout << "\n\ntest1\n";
  LinkedList list;

  list.insertEnd(1);
  list.insertEnd(2);
  list.insertFront(3);
  // some actions
  list.print();

  std::string expected = "3 1 2";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
}

void test2() {
  std::cout << "\n\ntest2\n";
  LinkedList list;

  list.insertFront(1);
  list.insertFront(2);
  list.insertEnd(3);
  list.insertFront(4);
  // some actions
  list.print();

  std::string expected = "4 2 1 3";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
}

int main() {
  test1();
  test2();
  // test3();

  // must see it, otherwise RTE
  std::cout << "\n\nNO RTE\n";

  return 0;
}

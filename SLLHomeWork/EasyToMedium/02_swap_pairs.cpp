#include <algorithm>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <utility>
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
    if (!head)
      return "";
    std::ostringstream oss;
    for (Node *cur = head; cur; cur = cur->next) {
      oss << cur->data;
      if (cur->next)
        oss << " ";
    }
    return oss.str();
  }

  // insertion functions
  void insertFront(int value) {
    Node *cur{new Node(value)};
    addNode(cur);
    if (head)
      cur->next = head;
    else
      tail = cur;
    head = cur;
    debugIntegrityCheck();
  }

  void insertEnd(int value) {
    Node *cur{new Node(value)};
    addNode(cur);
    if (tail)
      tail->next = cur;
    else
      head = cur;
    tail = cur;
    debugIntegrityCheck();
  }

  void insertNth(int pos, int value) {
    if (pos < 1)
      return;

    if (pos == 1) {
      insertFront(value);
      return;
    }

    Node *prev{getNth(pos - 1)};
    if (!prev)
      return;

    Node *cur{prev->next};

    if (!cur)
      return;

    Node *newNode{new Node(value)};
    addNode(newNode);
    newNode->next = cur;
    prev->next = newNode;
    debugIntegrityCheck();
  }

  // deletation fucnctions
  void deleteFront() {
    if (!head)
      return;

    Node *tmp{head};

    if (head == tail)
      tail = nullptr;

    head = head->next;
    deleteNode(tmp);
    debugIntegrityCheck();
  }

  void deleteNth(int pos) {
    if (pos < 1)
      return;

    if (pos == 1) {
      deleteFront();
      return;
    }

    Node *prev{getNth(pos - 1)};
    if (!prev)
      return;

    Node *cur{prev->next};

    if (!cur)
      return;

    prev->next = cur->next;
    deleteNode(cur);
    debugIntegrityCheck();
  }

  void deleteNextNode(Node *prev) {
    if (!prev)
      return;

    Node *cur{prev->next};
    if (!cur)
      return;

    if (cur == tail)
      tail = prev;
    prev->next = cur->next;
    deleteNode(cur);
    debugIntegrityCheck();
  }

  void deleteNodeWithKey(int value) { // O(n) time O(1) memroy
    if (!head)
      return;

    else if (head->data == value)
      deleteFront();

    else

      for (Node *cur = head->next, *prev = head; cur;
           prev = cur, cur = cur->next)
        if (cur->data == value) {
          deleteNextNode(prev);
          break;
        }
  }

  // teraversal functions
  Node *getNth(int pos) const {
    if (pos > 0 && head) {
      int cnt{0};
      for (Node *cur = head; cur; cur = cur->next)
        if (++cnt == pos)
          return cur;
    }
    return nullptr; // nullptr when empty list and not found
  }

  int search(int value) const {
    int idx{0};
    for (Node *cur = head; cur; cur = cur->next, ++idx)
      if (cur->data == value)
        return idx;
    return -1;
  }

  int improvedSearch(int value) const {
    int idx{0};
    Node *prev{};
    for (Node *cur = head; cur; prev = cur, cur = cur->next, ++idx)
      if (cur->data == value) {
        if (!prev)
          return idx;
        std::swap(prev->data, cur->data);
        return idx - 1;
      }

    return -1;
  }

  bool isSame(const LinkedList &other) const {
    Node *cur1{head};
    Node *cur2{other.head};

    while (cur1 && cur2) {
      if (cur1->data != cur2->data)
        return false;
      cur1 = cur1->next, cur2 = cur2->next;
    }
    return (!cur1 && !cur2); // they both should reach to end == false
  }

  ///////////////////////////// new function /////////////////////////////
  void swapPairs() { // O(n) time O(1) memory
    if (!head)
      return;
    if (head == tail)
      return;

    for (Node *prev = head, *cur = head->next; prev && cur;) {
      std::swap(cur->data, prev->data);
      prev = cur->next;
      if (prev)
        cur = prev->next;
    }
  }
  ///////////////////////////// new function /////////////////////////////

  int Size() const { return listLen; }

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
  list.swapPairs();
  list.print();

  std::string expected = "1";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list.debugVisualizer();
}

void test2() {
  std::cout << "\n\ntest2\n";
  LinkedList list;

  list.insertEnd(1);
  list.insertEnd(2);
  list.swapPairs();
  list.print();

  std::string expected = "2 1";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list.debugVisualizer();
}

void test3() {
  std::cout << "\n\ntest3\n";
  LinkedList list;

  list.insertEnd(1);
  list.insertEnd(2);
  list.insertEnd(3);
  list.insertEnd(4);
  list.swapPairs();
  list.print();

  std::string expected = "2 1 4 3";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list.debugVisualizer();
}

void test4() {
  std::cout << "\n\ntest4\n";
  LinkedList list;

  list.insertEnd(1);
  list.insertEnd(2);
  list.insertEnd(3);
  list.insertEnd(4);
  list.insertEnd(5);
  list.swapPairs();
  list.print();

  std::string expected = "2 1 4 3 5";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list.debugVisualizer();
}

int main() {
  test1();
  test2();
  test3();
  test4();

  std::cout << "\n\nNO RTE\n"; // must see it, otherwise RTE
  return 0;
}

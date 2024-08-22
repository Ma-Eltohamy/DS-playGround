#include <algorithm>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

struct Node {
  int data;
  Node *next{};
  Node *prev{};
  Node(int data) : data(data) {}
  ~Node() {
    std::cout << "Destroy value: " << data << " at address " << this << '\n';
  }
};

class LinkedList {
private:
  Node *head{};
  Node *tail{};
  int length{};

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

    if (node->prev)
      std::cout << node->prev->data;
    else
      std::cout << "X";

    std::cout << " <== [" << node->data << "] ==> ";

    if (node->next)
      std::cout << node->next->data;
    else
      std::cout << "X";

    if (node == head)
      std::cout << " [ head ]";
    if (node == tail)
      std::cout << " [ tail ]";

    std::cout << std::endl;
  }

  LinkedList(const LinkedList &) = delete;

  LinkedList &operator=(const LinkedList &) const = delete;

public:
  LinkedList(){};

  // debuggin functions
  void debugPrintAddress() {
    for (Node *cur = head; cur; cur = cur->next)
      std::cout << cur << "," << cur->data << "\t";
    std::cout << "\n";
  }

  void debugIntegrityCheck() const {
    if (!head) {
      assert(tail == nullptr);
      assert(length == 0);
      return;
    }

    assert(head);
    assert(tail);

    if (head == tail)
      assert(length == 1);

    else if (head->next == tail)
      assert(length == 2);

    else if (head->next != tail) {
      assert(length > 2);

      int len{0};
      Node *prev{};
      for (Node *cur = head; cur; prev = cur, cur = cur->next)
        ++len;

      assert(prev == tail);
      assert(len == (int)debugData.size()); // make sure they're all connected
      assert(len == length);
    }

    assert(head->prev == nullptr);
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
    ++length;
  }

  void deleteNode(Node *node) {
    debugDeleteNode(node);
    --length;
    delete node;
    node = nullptr;
  }

  std::string debugToStr() {
    if (!head)
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
  void link(Node *first, Node *second) {
    if (first)
      first->next = second;
    if (second)
      second->prev = first;
  }

  void insertEnd(int value) { // O(1) time O(1) memory
    Node *newNode(new Node(value));
    addNode(newNode);

    if (!head && !tail)
      head = tail = newNode;
    else
      link(tail, newNode), tail = newNode;
    debugIntegrityCheck();
  }

  void insertFront(int value) { // O(1) time O(1) memory
    Node *newNode(new Node(value));
    addNode(newNode);

    if (!head && !tail)
      head = tail = newNode;
    else {
      link(newNode, head);
      head = newNode;
    }
    debugIntegrityCheck();
  }

  void embedAfter(Node *nodeBefore, int value) {
    if (!nodeBefore)
      return;

    Node *newNode(new Node(value));
    addNode(newNode);

    Node *nodeAfter = nodeBefore->next;

    if (nodeAfter)
      link(nodeBefore, newNode), link(newNode, nodeAfter);
    else
      insertEnd(value);
    debugIntegrityCheck();
  }

  void insertSorted(int value) {
    if (!head || value <= head->data)
      insertFront(value);
    else if (value >= tail->data)
      insertEnd(value);

    else
      for (Node *cur = head; cur; cur = cur->next)
        if (value <= cur->data) {
          embedAfter(cur->prev, value);
          break;
        }
    debugIntegrityCheck();
  }

  // deletation fucnctions
  void deleteFront() {
    if (!head)
      return;

    Node *tmp = head->next;
    deleteNode(head);
    head = tmp;

    if (head)
      link(nullptr, head);
    else
      tail = nullptr;
    debugIntegrityCheck();
  }

  void deleteEnd() {
    if (!head)
      return;

    Node *tmp = tail->prev;
    deleteNode(tail);
    tail = tmp;

    if (tail)
      link(tail, nullptr);
    else
      head = nullptr;
    debugIntegrityCheck();
  }

  Node *deleteAndLink(Node *cur) {
    Node *prev{cur->prev};
    link(prev, cur->next);
    deleteNode(cur);
    return prev;
  }

  void deleteNodeWithKey(int value) {
    if (!head)
      return;

    if (head->data == value)
      deleteFront();
    else if (tail->data == value)
      deleteEnd();

    else
      for (Node *cur = head; cur; cur = cur->next)
        if (cur->data == value) {
          deleteAndLink(cur);
          break;
        }
    debugIntegrityCheck();
  }

  void deleteAllNodesWithKey(int value) { // O(n) time O(1) memory
    if (!head)
      return;

    insertFront(-value);
    for (Node *cur = head; cur;)
      if (cur->data == value) {
        cur = deleteAndLink(cur);
        if (!cur->next)
          tail = cur;
      } else
        cur = cur->next;
    deleteFront();
    debugIntegrityCheck();
  }

  void deleteEvenPositions() { // O(n) time O(1) memory
    if (!head || head == tail)
      return;

    for (Node *cur = head->next; cur; cur = cur->next->next) {
      cur = deleteAndLink(cur);
      if (!cur->next) {
        tail = cur;
        break;
      }
    }
  }

  void deleteOddPositions() {
    deleteFront();
    deleteEvenPositions();
  }

  bool isPalindrome() { // O(n) time O(1) memory
    if (!head || head == tail)
      return true;

    Node *left{head}, *right{tail};
    while (left && right) { // i don't want to depend on length
      if (left->data != right->data)
        return false;

      if (left->next == right->next || left->next == right)
        break;

      left = left->next, right = right->prev;
    }
    return true;

    // for (Node *left = head, *right = tail; left != right && right->next !=
    // left;
    //      left = left->next, right = right->prev)
    //   if (left->data != right->data)
    //     return false;
    // return true;
  }

  int middleValue1() {
    if (!head)
      return -1;

    Node *left{head}, *right{tail};
    while (left != right && left->next != right)
      left = left->next, right = right->prev;
    return right->data;
  }

  int middleValue2() {
    if (!head)
      return -1;

    // rotoise and hare algorithm
    Node *slow{head}, *fast{head};
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return slow->data;
  }
  ///////////////////////////// new function /////////////////////////////
  void swapKth(int k) { // O(n) time O(1) memory
    if (!head || head == tail || k <= 0)
      return;

    Node *left = head, *right = tail;
    while (--k && left && right) {
      left = left->next;
      right = right->prev;
    }

    if (!k && left != right) {
      // Swap head and tail if necessary
      if (left == head && right == tail)
        std::swap(head, tail);

      // Update connections
      Node *tmp = left->next;
      link(left->prev, tmp);
      link(right->prev, left);
      link(left, right->next);
      link(tmp->prev, right);

      // Handle consecutive nodes
      if (tmp != right)
        link(right, tmp);
      else
        link(right, left);
    }
    debugIntegrityCheck();
  }
  ///////////////////////////// new function /////////////////////////////

  // teraversal functions

  int Size() const { return length; }

  void print() const {
    std::cout << "\nprinted List: ";
    for (Node *cur = head; cur; cur = cur->next)
      std::cout << cur->data << ' ';
    std::cout << std::endl;
  }

  void printReversed() const {
    for (Node *cur = tail; cur; cur = cur->prev)
      std::cout << cur->data << ' ';
    std::cout << std::endl;
  }

  ~LinkedList() {
    for (auto node : debugData)
      delete node;
  }
};

void test0() {
  std::cout << "\n\ntest0\n";
  LinkedList list;

  list.insertEnd(1);
  list.insertEnd(2);
  list.insertEnd(3);
  list.insertEnd(4);
  list.insertEnd(5);
  list.swapKth(2);
  list.print();

  std::string expected = "1 4 3 2 5";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list.debugVisualizer();
}

void test1() {
  std::cout << "\n\ntest1\n";
  LinkedList list;

  list.insertEnd(1);
  list.insertEnd(2);
  list.insertEnd(3);
  list.insertEnd(4);
  list.insertEnd(5);
  list.swapKth(1);
  list.print();

  std::string expected = "5 2 3 4 1";
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
  list.insertEnd(3);
  list.insertEnd(4);
  list.insertEnd(5);
  list.swapKth(2);
  list.print();

  std::string expected = "1 4 3 2 5";
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
  list.insertEnd(5);
  list.insertEnd(6);

  list.swapKth(3);
  list.print();

  std::string expected = "1 2 4 3 5 6";
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
  list.insertEnd(6);

  list.swapKth(50000);
  list.print();

  std::string expected = "1 2 3 4 5 6";
  // std::string expected = "1 5 3 4 2 6";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list.debugVisualizer();
}
void test5() {
  std::cout << "\n\ntest5\n";
  LinkedList list;

  list.insertEnd(1);
  // list.insertEnd(2);
  // list.insertEnd(3);
  // list.insertEnd(4);
  // list.insertEnd(5);
  // list.insertEnd(6);

  list.swapKth(1);
  list.print();

  std::string expected = "1";
  // std::string expected = "1 5 3 4 2 6";
  std::string result = list.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list.debugVisualizer();
}

int main() {
  test0();
  test1();
  test2();
  test3();
  test4();
  test5();

  // must see it, otherwise RTE
  std::cout << "\n\nNO RTE\n";

  return 0;
}

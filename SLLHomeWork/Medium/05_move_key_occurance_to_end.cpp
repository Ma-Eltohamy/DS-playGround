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
  void reverse() { // O(n) time O(1) memory
    if (!head || head == tail)
      return;

    tail = head;
    Node *cur{head};
    Node *prev{};
    while (cur->next) {
      cur = cur->next;
      head->next = prev;
      prev = head;
      head = cur;
    }
    head->next = prev;
    debugIntegrityCheck();
  }
  void deleteEvenPositions() {
    if (!head || head == tail)
      return;

    for (Node *prev = head, *cur = head->next; cur; prev = prev->next) {
      deleteNextNode(prev);
      if (!prev->next)
        break;
      cur = prev->next->next;
    }
  }

  void embedAfter(Node *prev, int value) {
    if (!prev)
      return;

    Node *node{new Node(value)};
    addNode(node);
    node->next = prev->next;
    prev->next = node;

    // no update for head ptr but tail should be updated if needed
    if (prev == tail)
      tail = tail->next;
  }

  void insertSorted(int value) { // O(n) time O(1) time
    if (!head || value <= head->data)
      insertFront(value);

    else if (tail->data <= value)
      insertEnd(value);

    else {
      for (Node *cur = head->next, *prev = head; cur != tail;
           prev = cur, cur = cur->next)
        if (cur->data >= value) {
          embedAfter(prev, value);
          break;
        }
    }
  }

  void swapHeadTail() {

    if (!head || head == tail)
      return;

    else if (tail == head->next) {
      tail->next = head;
      head->next = nullptr;
      std::swap(head, tail);
    }

    else {
      Node *prev{getNth(listLen - 1)};

      tail->next = head->next;
      prev->next = head;
      head->next = nullptr;
      std::swap(head, tail);

      debugIntegrityCheck();
    }
  }

  void leftRotate(int times) { // O(n) time O(1) memroy
    if (!head || head == tail || !(times %= listLen))
      return;

    Node *prev{getNth(times)};
    if (!prev)
      return;

    tail->next = head;
    head = prev->next;
    prev->next = nullptr;
    tail = prev;

    debugIntegrityCheck();
  }
  void removeDuplicates() { // O(n^2) time O(1) memory
    if (!head || head == tail)
      return;

    for (Node *cur1 = head; cur1; cur1 = cur1->next) {
      for (Node *prev = cur1, *cur2 = prev->next; cur2;) {
        if (cur1->data == cur2->data)
          deleteNextNode(prev), cur2 = prev->next;
        else
          prev = prev->next, cur2 = prev->next;
      }
    }
    debugIntegrityCheck();
  }

  void deleteLastOccurance(int value) {
    if (!head)
      return;

    Node *beforeLast{};

    if (head->data == value)
      beforeLast = head;

    for (Node *prev = head; prev->next; prev = prev->next)
      if (prev->next->data == value)
        beforeLast = prev;

    if (beforeLast == head)
      deleteFront();
    else
      deleteNextNode(beforeLast);
    debugIntegrityCheck();
  }

  void moveToEnd(Node *prev, Node *cur) { // O(1) time O(1) memory
    if (!cur || cur == tail)
      return;

    if (!prev && cur == head)
      head = head->next;
    else
      prev->next = cur->next;

    cur->next = tail->next;
    tail->next = cur;
    tail = cur;
  }

  ///////////////////////////// new function /////////////////////////////
  void moveKeyOccuranceToEnd(int value) { // O(n)time O(1) memroy
    if (!head || head == tail)
      return;

    Node *oldTail{tail};

    for (Node *prev{}, *cur{head}, *next{cur->next}; cur != oldTail;) {
      if (cur->data == value) {
        moveToEnd(prev, cur);
        cur = next;
        next = next->next;
      } else
        prev = cur, cur = next, next = next->next;
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
  LinkedList list1;

  list1.insertEnd(1);
  list1.insertEnd(2);
  list1.insertEnd(3);
  list1.insertEnd(2);
  list1.insertEnd(4);
  list1.insertEnd(1);
  list1.moveKeyOccuranceToEnd(1);

  std::string expected = "2 3 2 4 1 1";
  std::string result = list1.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list1.debugVisualizer();
}

void test2() {
  std::cout << "\n\ntest2\n";
  LinkedList list1;

  list1.insertEnd(5);
  list1.insertEnd(2);
  list1.insertEnd(3);
  list1.insertEnd(2);
  list1.insertEnd(1);
  list1.insertEnd(1);
  list1.moveKeyOccuranceToEnd(1);

  std::string expected = "5 2 3 2 1 1";
  std::string result = list1.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list1.debugVisualizer();
}

void test3() {
  std::cout << "\n\ntest3\n";
  LinkedList list1;

  list1.insertEnd(1);
  list1.insertEnd(1);
  list1.insertEnd(1);
  list1.insertEnd(1);
  list1.insertEnd(1);
  list1.insertEnd(1);
  list1.moveKeyOccuranceToEnd(1);

  std::string expected = "1 1 1 1 1 1";
  std::string result = list1.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list1.debugVisualizer();
}

void test4() {
  std::cout << "\n\ntest4\n";
  LinkedList list1;

  list1.insertEnd(1);
  list1.insertEnd(2);
  list1.insertEnd(3);
  list1.insertEnd(1);
  list1.insertEnd(2);
  list1.insertEnd(4);
  list1.insertEnd(1);
  list1.insertEnd(7);
  list1.insertEnd(1);
  list1.insertEnd(8);
  list1.insertEnd(1);
  list1.insertEnd(1);
  list1.moveKeyOccuranceToEnd(1);

  std::string expected = "2 3 2 4 7 8 1 1 1 1 1 1";
  std::string result = list1.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list1.debugVisualizer();
}

void test5() {
  std::cout << "\n\ntest5\n";
  LinkedList list1;

  list1.insertEnd(1);
  list1.insertEnd(2);
  list1.insertEnd(3);
  list1.insertEnd(4);

  list1.moveKeyOccuranceToEnd(4);

  std::string expected = "1 2 3 4";
  std::string result = list1.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list1.debugVisualizer();
}
void test6() {
  std::cout << "\n\ntest5\n";
  LinkedList list1;

  list1.insertEnd(1);
  list1.insertEnd(2);

  list1.moveKeyOccuranceToEnd(1);

  std::string expected = "2 1";
  std::string result = list1.debugToStr();
  if (expected != result) {
    std::cout << "no match:\nExpected: " << expected << "\nResult  : " << result
              << "\n";
    assert(false);
  }
  list1.debugVisualizer();
}

int main() {
  test6();
  test5();

  test1();
  test2();
  test3();
  test4();

  std::cout << "\n\nNO RTE\n"; // must see it, otherwise RTE
  return 0;
}

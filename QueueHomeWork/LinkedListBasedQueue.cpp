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

  void print() const {
    std::cout << "\nprinted List: ";
    for (Node *cur = head; cur; cur = cur->next)
      std::cout << cur->data << ' ';
    std::cout << std::endl;
  }

  int front() { return head->data; }
  int Size() const { return listLen; }
};

class Queue {
private:
  LinkedList list;

public:
  void enqueue(int value) { list.insertEnd(value); }

  int dequeue() {
    int tmp = list.front();
    list.deleteFront();
    return tmp;
  }

  void display() { list.print(); }
  bool isEmpty() { return list.Size() == 0; }
};

int main(int argc, char *argv[]) {

  Queue q;
  for (int i = 0; i < 10; ++i)
    q.enqueue(i);
  q.display();

  std::cout << "Start dequeing\n";
  for (int i = 0; i < 10; ++i)
    q.dequeue();
  std::cout << std::endl;
  std::cout << "End of dequeing\n";
  q.display();

  return 0;
  return 0;
}

#include <iostream>

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

public:
  LinkedList(){};

  void insertEnd(int value) { // O(1)time O(1) memory
    Node *cur{new Node(value)};
    if (tail)
      tail->next = cur;
    else
      head = cur;
    tail = cur;
    ++listLen;
  }

  void print() const { // O(n) time - O(1) memory
    std::cout << "\nprinted List: ";
    for (Node *cur = head; cur; cur = cur->next)
      std::cout << cur->data << ' ';
    std::cout << std::endl;
  }

  ///////////////////////////// new function /////////////////////////////
  ~LinkedList() { // O(n) time O(1) memory
    while (head) {
      Node *current = head->next;
      delete head;
      head = current;
    }
  }
  ///////////////////////////// new function /////////////////////////////
};

int main(int argc, char *argv[]) {
  LinkedList list;
  list.insertEnd(6);
  list.insertEnd(10);
  list.insertEnd(8);
  list.insertEnd(15);
  return 0;
}

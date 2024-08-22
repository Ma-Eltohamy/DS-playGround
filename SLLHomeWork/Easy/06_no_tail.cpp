#include <iostream>
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

public:
  ///////////////////////////// new function /////////////////////////////
  void print() const {
    std::cout << "\nprinted List: ";
    for (Node *cur = head; cur; cur = cur->next)
      std::cout << cur->data << ' ';
    std::cout << std::endl;
  }

  void addElement(int value) { // O(1) time O(1) memory
    Node *cur{new Node(value)};
    cur->next = head;
    head = cur;
  }
  Node *getTail() { // O(n) time O(1) memroy
    // Node *cur = head;
    // while (cur) {
    //   if (!cur->next)
    //     return cur;
    //   cur = cur->next;
    // }
    // return nullptr;

    Node *cur;
    for (/* Node *cur = head */; cur->next; cur = cur->next)
      ;
    return cur;
  }
  ~LinkedList() { // O(n) time O(1)memroy
    for (Node *cur = head; head->next; cur = head) {
      head = head->next;
      delete cur;
    }
    delete head;
  }
  ///////////////////////////// new function /////////////////////////////
};

int main() {
  LinkedList list;

  list.addElement(10);
  list.addElement(20);
  list.addElement(30);
  list.addElement(40);
  list.addElement(50);
  list.addElement(60);

  list.print();                 // 60 50 40 30 20 10
  cout << list.getTail()->data; // 10

  // must see it, otherwise RTE
  std::cout << "\n\nNO RTE\n";

  return 0;
}

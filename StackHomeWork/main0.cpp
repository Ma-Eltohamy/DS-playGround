#include <cassert>
#include <iostream>

struct Node {
  int data{};
  Node *next{};
  Node(int data) : data(data) {}
  ~Node() {
    std::cout << "Destroy value: " << data << " at address " << this << '\n';
  }
};

class Stack {
private:
  int length{};
  Node *head{};

public:
  void push(int value) {
    Node *newNode(new Node(value));
    newNode->next = head;
    head = newNode;
  }
  int peek() {
    assert(!isEmpty());
    return head->data;
  }
  int pop() {
    assert(!isEmpty());
    int tmpData = head->data;
    Node *tmp = head;
    head = head->next;
    delete tmp;
    return tmpData;
  }

  bool isEmpty() { return !head; }

  void display() {
    for (Node *cur = head; cur; cur = cur->next)
      std::cout << cur->data << " ";
    std::cout << "\n";
  }
  ~Stack() {
    while (isEmpty())
      pop();
  }
};
int main(int argc, char *argv[]) {
  Stack stk;
  stk.push(10);
  stk.push(20);
  stk.push(30);

  stk.display();                   // 30 20 10
  std::cout << stk.peek() << "\n"; // 30

  while (!stk.isEmpty())
    std::cout << stk.pop() << std::endl;
  // 30 20 10
  return 0;
}

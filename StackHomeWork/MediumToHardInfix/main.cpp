#include <assert.h>
#include <iostream>

class Stack {
private:
  struct Node {
    int data{};
    Node *next{};
    Node *prev{};
    Node(int data) : data(data) {}
  };

  Node *head{}; // Points to Top
  Node *middle{};
  int length{0};

public:
  ~Stack() {
    while (!isEmpty())
      pop();
  }

  void link(Node *first, Node *second) {
    if (first)
      first->next = second;
    if (second)
      second->prev = first;
  }

  void display() {
    for (Node *cur = head; cur; cur = cur->next) {
      if (cur == middle)
        std::cout << '[' << cur->data << ']';
      else
        std::cout << cur->data;
      std::cout << ' ';
    }
    std::cout << "\n";
  }

  void push(int value) {
    // By design: always new node = head
    // Great match with stack!
    Node *item = new Node(value);
    length++;
    if (!head)
      head = item;
    else {
      link(item, head);
      head = item;
    }
    if (length <= 1)
      middle = head;
    else if (length % 2 == 1)
      middle = middle->prev;
  }

  // Tip: This code works as long as machine has more RAM
  // In industry: You may check if return is null (can't create) or not.

  int pop() {
    assert(!isEmpty());
    int element = head->data;
    Node *temp = head;
    head = head->next;
    delete temp;
    length--;
    if (head)
      head->prev = nullptr;

    if (length <= 1)
      middle = head;
    else if (length % 2 == 0)
      middle = middle->next;
    return element;
  }

  int peek() {
    assert(!isEmpty());
    int element = head->data;
    return element;
  }

  int isEmpty() { return !head; }
};
int main(int argc, char *argv[]) {

  Stack stk;
  for (int i = 0; i < 10; ++i) {
    stk.push(i);
    stk.display();
  }
  while (!stk.isEmpty()) {
    stk.pop();
    stk.display();
  }
  return 0;
}

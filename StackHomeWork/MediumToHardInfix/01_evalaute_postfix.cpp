#include <assert.h>
#include <cctype>
#include <cmath>
#include <iostream>
template <typename T> struct Node {
  T data{};
  Node *next{};
  Node(T data) : data(data) {}
  ~Node() {
    // std::cout << "Destroy value: " << data << " at address " << this << '\n';
  }
};
template <typename T> class Stack {
private:
  T length{};
  Node<T> *head{};

public:
  void push(T value) {
    Node<T> *newNode(new Node(value));
    newNode->next = head;
    head = newNode;
  }
  T peek() {
    assert(!isEmpty());
    return head->data;
  }
  T pop() {
    assert(!isEmpty());
    T tmpData = head->data;
    Node<T> *tmp = head;
    head = head->next;
    delete tmp;
    return tmpData;
  }

  bool isEmpty() { return !head; }

  void display() {
    for (Node<T> *cur = head; cur; cur = cur->next)
      std::cout << cur->data << " ";
    std::cout << "\n";
  }
  ~Stack() {
    while (isEmpty())
      pop();
  }
};

double operation(double A, double B, char oper) {
  if (oper == '+')
    return A + B;
  else if (oper == '-')
    return A - B;
  else if (oper == '*')
    return A * B;
  else if (oper == '/')
    return A / B;
  return std::pow(A, B);
}

double evaluatePostfix(std::string postfix) {
  int length{(int)postfix.size()};
  Stack<double> s;
  double A{}, B{}, result{};

  for (int i = 0; i < length; ++i) {
    if (std::isdigit(postfix[i]))
      s.push(postfix[i] - '0');
    else {
      A = s.pop();
      B = s.pop();
      s.push(operation(B, A, postfix[i]));
    }
  }
  return s.peek();
}
int main(int argc, char *argv[]) {
  // some operations
  std::string Strs[6]{"52/", "12+3+", "123*+", "23*4+", "135*+72/-", "432^^"};

  for (std::string str : Strs)
    std::cout << evaluatePostfix(str) << ' ';
  std::cout << std::endl;
  return 0;
}

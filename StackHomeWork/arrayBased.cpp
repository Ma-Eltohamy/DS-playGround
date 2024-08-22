#include <cassert>
#include <iostream>

class Stack {
private:
  int size{};
  int top{};
  int *array{};

public:
  Stack(int size) : top{-1}, size(size), array(new int[size]) {}

  void push(int value) {
    assert(!isFull());
    array[++top] = value;
  }

  int pop() {
    assert(!isEmpty());
    return array[top--];
  }

  int peek() {
    assert(!isEmpty());
    return array[top];
  }
  bool isFull() { return (top == size - 1); }
  bool isEmpty() { return (top == -1); }

  void display() {
    for (int i = top; top >= 0; --i)
      std::cout << array[i] << ' ';
    std::cout << std::endl;
  }

  ~Stack() { delete[] array; }
};
int main(int argc, char *argv[]) {
  Stack s(5);
  std::cout << s.isFull() << ' ' << s.isEmpty() << '\n';
  s.display();
  return 0;
}

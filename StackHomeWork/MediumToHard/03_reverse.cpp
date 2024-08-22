#include <assert.h>
#include <iostream>
#include <utility>

// simple trick to avoid re-changing the class
typedef int type;

class Stack {
private:
  int size{};
  int top{};
  type *array{};

public:
  Stack(int size) : size(size), top(-1) { array = new type[size]; }

  ~Stack() { delete[] array; }

  void push(type x) {
    assert(!isFull());
    array[++top] = x;
  }

  type pop() {
    assert(!isEmpty());
    return array[top--];
  }

  type peek() {
    assert(!isEmpty());
    return array[top];
  }

  void insertAtBottom(int x) {
    if (isEmpty())
      push(x);

    else {
      int topNum = array[top];
      pop();
      insertAtBottom(x);
      push(topNum);
    }
  }

  void reverse() { // O(n^2) quadritice time O(n) memory
    // But it should be O(n) by applying insertAtBottom in reverse body
    if (top == 0)
      return;

    int topNum = array[top];
    pop();
    reverse();
    insertAtBottom(topNum);
  }

  int isFull() { return top == size - 1; }

  int isEmpty() { return top == -1; }

  void display() {
    for (int i = top; i >= 0; --i)
      std::cout << array[i] << ' ';
    std::cout << std::endl;
  }

  void display_reversed() {
    for (int i = 0; i <= top; i++)
      std::cout << array[i] << " ";
    std::cout << "\n";
  }
};
int main(int argc, char *argv[]) {
  // some operations
  Stack stk(10);
  stk.push(1);
  stk.push(2);
  stk.push(3);
  stk.display(); // 3 2 1
  stk.reverse();
  stk.display(); // 1 2 3

  return 0;
}

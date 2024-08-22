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

  // void insertAtBottom(int x, bool firstTime = true) { // O(n) time O(n)
  // memory
  //   if (firstTime)
  //     push(x);
  //
  //   x = top - 1;
  //   std::swap(array[x], array[top]);
  //   if (!x)
  //     return;
  //
  //   --top;
  //   insertAtBottom(x, false);
  //   ++top;
  // }
  void insertAtBottom(int x) {
    if (isEmpty())
      push(x);

    else {
      int topNum = array[top];
      pop(); // usually pop function doesn't return int just popping
      insertAtBottom(x);
      push(topNum);
    }
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
  stk.insertAtBottom(7);
  stk.display(); // 3 2 1 7
  stk.insertAtBottom(10);
  stk.display(); // 3 2 1 7 10

  return 0;
}

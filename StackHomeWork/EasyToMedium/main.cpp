#include <assert.h>
#include <iostream>

class Stack {
private:
  int size{};
  int capacity{};
  int top1{};
  int top2{};
  int *array{};

public:
  Stack(int size) : size(size), capacity(size * 2), top2(size - 1), top1(-1) {
    array = new int[capacity];
  }

  ~Stack() { delete[] array; }

  void push(int id, int x) {
    assert(!isFull(id));
    if (id - 1)
      array[++top2] = x;
    else
      array[++top1] = x;
  }

  int pop(int id) {
    assert(!isEmpty(id));
    if (id - 1)
      return array[top2--];
    return array[top1--];
  }

  int peek(int id) {
    assert(!isEmpty(id));
    if (id - 1)
      return array[top2];
    return array[top1];
  }

  int isFull(int id) {
    if (id - 1)
      return top2 == capacity - 1;
    return top1 == size - 1;
  }

  int isEmpty(int id) {
    if (id - 1)
      return top2 == size - 1;
    return top1 == -1;
  }

  void display() {
    for (int i = top1; i >= 0; --i)
      std::cout << array[i] << " ";
    std::cout << "\n";
    for (int i = top2; i >= size; --i)
      std::cout << array[i] << " ";
    std::cout << "\n";
  }
};
int main(int argc, char *argv[]) {
  Stack stk(10);
  stk.push(2, 0);
  stk.push(2, 1);
  stk.push(2, 2);
  stk.push(2, 3);
  stk.push(2, 4);
  stk.push(2, 5);
  stk.push(2, 6);
  stk.pop(2);
  stk.push(2, 10);
  stk.push(2, 7);
  stk.push(2, 8);
  stk.push(2, 9);

  stk.push(1, 0);
  stk.push(1, 1);
  stk.push(1, 2);
  stk.push(1, 3);
  stk.push(1, 4);
  stk.push(1, 5);
  stk.push(1, 6);
  stk.push(1, 7);
  stk.push(1, 8);
  stk.push(1, 9);
  stk.display();
  return 0;
}

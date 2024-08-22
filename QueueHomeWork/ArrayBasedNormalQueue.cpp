#include <cassert>
#include <iostream>

class Queue {
private:
  int idx{}, capacity{};
  int *array{};

public:
  Queue(int capacity) : idx(-1), capacity(capacity), array(new int[capacity]) {}

  void enqueue(int value) {
    assert(!isFull());
    array[++idx] = value;
  }

  void shiftLeft() {
    for (int i = 0; i <= idx; ++i)
      array[i] = array[i + 1];
  }

  int &front() {
    assert(!isEmpty());
    return array[0];
  }

  int dequeue() {
    int tmp = array[0];
    --idx;
    shiftLeft();
    return tmp;
  }
  void display() {
    if (isEmpty())
      std::cout << "\n==> Queue is Empty!\n";
    for (int i = 0; i <= idx; ++i)
      std::cout << array[i] << ' ';
    std::cout << std::endl;
  }
  bool isFull() { return idx == capacity - 1; }
  bool isEmpty() { return idx == -1; }
};
int main(int argc, char *argv[]) {
  // soem operations
  Queue q(10);
  for (int i = 0; i < 10; ++i)
    q.enqueue(i);
  q.display();

  std::cout << "Start dequeing\n";
  for (int i = 0; i < 10; ++i)
    std::cout << q.dequeue() << ' ';
  std::cout << std::endl;
  std::cout << "End of dequeing\n";
  q.display();

  return 0;
}

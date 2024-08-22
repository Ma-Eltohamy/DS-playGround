#include <cassert>
#include <iostream>

class Queue {
private:
  int capacity{}, front{}, rear{}, addedEelements{};
  int *array{};

public:
  Queue(int capacity)
      : capacity(capacity), front{0}, rear(0), addedEelements(0),
        array(new int[capacity]) {}

  ~Queue() { delete[] array; }

  int next(int idx) {
    if (idx == capacity - 1)
      return 0;
    return ++idx;
  }

  int prev(int idx) {
    if (idx == 0)
      return capacity - 1;
    return --idx;
  }

  void enqueue(int value) {
    assert(!isFull());

    array[rear] = value;
    rear = next(rear);
    ++addedEelements;
  }

  int dequeue() {
    assert(!isEmpty());
    front = next(front);
    --addedEelements;
    return array[prev(front)];
  };

  void display() {
    std::cout << "Front " << front << " - rear " << rear << "\t";
    if (isFull())
      std::cout << "full";
    else if (isEmpty()) {
      std::cout << "empty\n\n";
      return;
    }
    std::cout << "\n";
    for (int i = 0, tmp = front; i < addedEelements; ++i, tmp = next(tmp))
      std::cout << array[tmp] << ' ';
    std::cout << "\n\n";
  }
  bool isFull() { return addedEelements == capacity; }
  bool isEmpty() { return addedEelements == 0; }
  int size() { return addedEelements; }
};
int main(int argc, char *argv[]) {
  // some operations
  Queue qu(6);
  assert(qu.isEmpty());
  qu.display();

  for (int i = 1; i <= 6; ++i) {
    assert(!qu.isFull());
    qu.enqueue(i);
    qu.display();
  }
  assert(qu.isFull());

  for (int i = 1; i <= 6; ++i) {
    assert(!qu.isEmpty());
    qu.dequeue();
    qu.display();
  }

  for (int i = 1; i <= 6; ++i) {
    assert(!qu.isFull());
    qu.enqueue(i);
    qu.display();
  }

  qu.dequeue();
  assert(!qu.isFull());
  qu.enqueue(7);
  assert(qu.isFull());
  qu.display();

  qu.dequeue();
  qu.dequeue();
  assert(!qu.isFull());
  qu.enqueue(8);
  assert(!qu.isFull());
  qu.display();
  qu.enqueue(9);
  assert(qu.isFull());
  qu.display();

  for (int i = 1; i <= 6; ++i) {
    assert(!qu.isEmpty());
    qu.dequeue();
    qu.display();
  }

  return 0;
}

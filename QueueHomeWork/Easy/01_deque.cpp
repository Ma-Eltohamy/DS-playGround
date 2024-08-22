#include <cassert>
#include <iostream>

class Deque {
private:
  int capacity{}, front{}, rear{}, addedEelements{};
  int *array{};

public:
  Deque(int capacity)
      : capacity(capacity), front{0}, rear(0), addedEelements(0),
        array(new int[capacity]) {}

  ~Deque() { delete[] array; }

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

  void enqueueRear(int value) {
    assert(!isFull());

    array[rear] = value;
    rear = next(rear);
    ++addedEelements;
  }

  void enqueueFront(int value) {
    assert(!isFull());
    front = prev(front);
    array[front] = value;
    ++addedEelements;
  }

  int dequeueRear() {
    assert(!isEmpty());
    rear = prev(rear);
    --addedEelements;
    return array[rear];
  }

  int dequeueFront() {
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
  Deque dq(6);

  dq.enqueueFront(3);
  dq.display();
  dq.enqueueFront(2);
  dq.enqueueRear(4);
  dq.enqueueFront(1);
  dq.enqueueFront(5);
  dq.enqueueFront(6);
  dq.display();
  std::cout << dq.dequeueRear() << "\n";
  dq.display();
  std::cout << dq.dequeueFront() << "\n";
  dq.display();
  std::cout << dq.dequeueRear() << "\n";
  std::cout << dq.dequeueFront() << "\n";

  while (!dq.isEmpty())
    dq.dequeueRear();
  dq.display(); //
  for (int i = 0; i < 6; ++i)
    dq.enqueueRear(i + 10);
  dq.display(); //

  return 0;
}

/*
Front 5 - rear 0
3

Front 1 - rear 1	full
6 5 1 2 3 4

4
Front 1 - rear 0
6 5 1 2 3

6
Front 2 - rear 0
5 1 2 3

3
5
Front 3 - rear 3	empty

Front 3 - rear 3	full
10 11 12 13 14 15


 */

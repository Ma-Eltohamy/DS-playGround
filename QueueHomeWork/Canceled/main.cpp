#include <assert.h>
#include <iostream>

// Dr.Mostafa solution was about adding a new extra memeory insted of these two
// bools.
// It would be more memory efficent than this but this solution is good, too.
//
// Explaning Dr.Mostafa's solution
//
// By adding one more cell in the array we can use it to check if the rear next
// is the front.
// If so, then that's mean for the user--> "you have reached to
// the max number of element you can have.";

class Queue {
private:
  // I keept the deal of making the rear always looking on an avilable place to
  // put on it, but we could make the rear insted of looking on the avilable
  // spot. We could make it looks to the last element in the array
  int capacity{}, front{}, rear{};
  bool empty{}, full{};
  int *array{};

public:
  Queue(int capacity)
      : capacity(capacity), front(0), rear(0), array(new int[capacity]),
        empty(true), full{false} {}
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

  // We have to put in consideration dequeue function must change
  // 1) full --> to true if it was notFull (false)
  // 2) empty --> to false if it was empty(true)
  void enqueue(int value) {
    assert(!isFull());
    array[rear] = value;
    rear = next(rear);
    if (rear == front)
      full = true;
    if (empty)
      empty = false;
  }

  // We have to put in consideration dequeue function must change
  // 1) full --> to false if it was full (true)
  // 2) empty --> to true if it was notEmpty(false)
  int dequeue() {
    assert(!isEmpty());
    front = next(front);
    if (front == rear)
      empty = true;
    if (full)
      full = false;
    return array[prev(front)];
  }

  void display() {
    std::cout << "Front " << front << " - rear " << rear << "\t";
    if (isFull())
      std::cout << "full";
    else if (isEmpty()) {
      std::cout << "empty\n\n";
      return;
    }
    std::cout << "\n";

    std::cout << array[front] << ' ';
    for (int cur = next(front); cur != rear; cur = next(cur))
      std::cout << array[cur] << " ";
    std::cout << "\n\n";
  }

  bool isEmpty() { return empty; }

  bool isFull() { return full; }
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
    // qu.display();
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

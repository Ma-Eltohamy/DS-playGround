#include <cassert>
#include <iostream>
#include <utility>

class PriorityQueue {
private:
  int size, capacity;
  std::pair<int, int> *array;

  int getLeft(int idx) {
    int left = idx * 2 + 1;
    // At the end left must be in range [1 , size - 1]

    if (left <= 0 || left >= size)
      return -1;
    return left;
  }

  int getRight(int idx) {
    int right = idx * 2 + 2;
    // At the end right must be in range [2 , size - 1]

    if (right <= 1 || right >= size)
      return -1;
    return right;
  }

  int getParent(int idx) {
    int parent = (idx - 1) / 2;

    if (idx == 0 || parent < 0 || parent >= size)
      return -1;
    return parent;
  }

  void heapifyUp(int childIdx) { // O(log n) time
    int parentIdx{getParent(childIdx)};
    if (parentIdx == -1 || array[parentIdx].second >= array[childIdx].second)
      return;

    std::swap(array[childIdx], array[parentIdx]);
    heapifyUp(parentIdx);
  }

  void heapifyDown(int rootIdx) { // O(log n) time
    // rootIdx must be valid if it has leftChildIdx or rightChildIdx
    int leftChildIdx{getLeft(rootIdx)};
    int rightChildIdx{getRight(rootIdx)};
    int maxChildIdx{leftChildIdx};

    if (maxChildIdx == -1 ||
        (rightChildIdx != -1 &&
         array[maxChildIdx].second < array[rightChildIdx].second))
      maxChildIdx = rightChildIdx;

    if (maxChildIdx == -1 || array[rootIdx].second > array[maxChildIdx].second)
      return;

    std::swap(array[rootIdx], array[maxChildIdx]);
    heapifyDown(maxChildIdx);
  }

  void heapify() {
    for (int i = size - 1; i >= 0; --i)
      heapifyDown(i);
  }

public:
  PriorityQueue()
      : size{0}, capacity(1000), array(new std::pair<int, int>[capacity]) {}

  ~PriorityQueue() { delete[] array; }

  int top() {
    assert(!isEmpty());
    return array[0].first;
  }

  void enqueue(int key, int priority) {
    array[size++] = std::make_pair(key, priority);
    heapifyUp(size - 1);
  }

  std::pair<int, int> dequeue() {
    assert(!isEmpty());
    std::pair<int, int> max = array[0];
    array[0] = array[size - 1];
    --size;
    heapifyDown(0);
    return max;
  }

  bool isEmpty() { return size == 0; }

  // For debuggin
  void print() {
    std::cout << "\n\n********* Start Printing Binary Heap *********\n";
    for (int i = 0; i < size; ++i)
      std::cout << array[i].first << ' ';
    std::cout << "\n********** End Printing Binary Heap **********\n\n";
  }
};

int main(int argc, char *argv[]) {
  PriorityQueue tasks;

  tasks.enqueue(1131, 1);
  tasks.enqueue(3111, 3);
  tasks.enqueue(2211, 2);
  tasks.enqueue(3161, 3);
  tasks.enqueue(7761, 7);

  std::pair<int, int> max{tasks.dequeue()};
  std::cout << max.first << ' ' << max.second << '\n';
  max = tasks.dequeue();
  std::cout << max.first << ' ' << max.second << '\n';

  tasks.enqueue(1535, 1);
  tasks.enqueue(2815, 2);
  tasks.enqueue(3845, 3);
  tasks.enqueue(3145, 3);

  while (!tasks.isEmpty()) {
    max = tasks.dequeue();
    std::cout << '(' << max.first << ' ' << max.second << ')' << '\n';
  }
  std::cout << '\n';

  return 0;
}

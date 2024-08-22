#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

class MinHeap {
private:
  int size, capacity, *array;

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
    if (parentIdx == -1 || array[parentIdx] < array[childIdx])
      return;

    std::swap(array[childIdx], array[parentIdx]);
    heapifyUp(parentIdx);
  }

  void heapifyDown(int rootIdx) { // O(log n) time
    // rootIdx must be valid if it has leftChildIdx or rightChildIdx
    int leftChildIdx{getLeft(rootIdx)};
    int rightChildIdx{getRight(rootIdx)};
    int minChildIdx{leftChildIdx};

    if (minChildIdx == -1 || (minChildIdx != -1 && rightChildIdx != -1 &&
                              array[minChildIdx] > array[rightChildIdx]))
      minChildIdx = rightChildIdx;

    if (minChildIdx == -1 || array[rootIdx] < array[minChildIdx])
      return;

    std::swap(array[rootIdx], array[minChildIdx]);
    heapifyDown(minChildIdx);
  }

  void heapify() {
    for (int i = size - 1; i >= 0; --i)
      heapifyDown(i);
  }

public:
  MinHeap() : size{0}, capacity(1000), array(new int[capacity]) {}
  MinHeap(std::vector<int> &v) {
    assert(capacity >= (int)v.size());
    array = new int[capacity]{};
    size = (int)v.size();

    for (int i = 0; i < size; ++i)
      array[i] = v[i];

    heapify();
  }
  ~MinHeap() { delete[] array; }

  int top() {
    assert(!isEmpty());
    return array[0];
  }
  void push(int key) {
    array[size++] = key;
    heapifyUp(size - 1);
  }
  void pop() {
    assert(!isEmpty());
    array[0] = array[size - 1];
    --size;
    heapifyDown(0);
  }
  bool isEmpty() { return size == 0; }

  void heapSort() {
    int oldSize = size;
    --size;
    for (; size; --size) {
      std::swap(array[0], array[size]);
      heapifyDown(0);
    }
    size = oldSize;

    for (int i = 0; i < size / 2; ++i)
      std::swap(array[i], array[size - i - 1]);
  }

  // For debuggin
  void print() {
    std::cout << "\n\n********* Start Printing Binary Heap *********\n";
    for (int i = 0; i < size; ++i)
      std::cout << array[i] << ' ';
    std::cout << "\n********** End Printing Binary Heap **********\n\n";
  }
};

void creat_heap_nlogn() {
  MinHeap heap;

  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

  for (int i = 0; i < v.size();
       ++i)          // O(n log n) // n --> to push every element in the vec
    heap.push(v[i]); // Only takes (log n) time

  while (!heap.isEmpty()) {         // O(n log n) n --> To get every element
    std::cout << heap.top() << " "; // O(1) time
    heap.pop();                     // O(log n) time
  }
  // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
}
int main(int argc, char *argv[]) {
  MinHeap heap;
  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
  // int arr[14]{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

  for (int i = 0; i < v.size(); ++i)
    heap.push(v[i]);
  heap.print();
  heap.heapSort();
  heap.print();
  // creat_heap_nlogn();
  // heap.print();
  return 0;
}

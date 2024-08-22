#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

class MaxHeap {
private:
  int size, capacity, *arr;

  int getLeft(int rootIdx) {
    int left = rootIdx * 2 + 1;

    if (left <= 0 || left >= size)
      return -1;
    return left;
  }

  int getRight(int rootIdx) {
    int right = rootIdx * 2 + 2;

    if (right <= 1 || right >= size)
      return -1;
    return right;
  }

  int getParent(int rootIdx) {
    int parent = (rootIdx - 1) / 2;

    // We can find a formual to tell us wehre nodes start from base of size
    // To avoid get them as parent
    if (rootIdx == 0 || parent < 0 || parent >= size)
      return -1;
    return parent;
  }

  void heapifyUp(int rootIdx) {
    int parent{getParent(rootIdx)};

    if (parent == -1 || arr[parent] > arr[rootIdx])
      return;
    std::swap(arr[parent], arr[rootIdx]);
    heapifyUp(parent);
  }
  void heapifyDown(int rootIdx) {
    int left{getLeft(rootIdx)};
    int right{getRight(rootIdx)};
    int mxChild{left};

    if (mxChild == -1 ||
        (mxChild != -1 && right != -1 && arr[mxChild] < arr[right]))
      mxChild = right;

    if (mxChild == -1 || arr[mxChild] < arr[rootIdx])
      return;

    std::swap(arr[mxChild], arr[rootIdx]);
    heapifyDown(mxChild);
  }

  void heapify() { // O(n)
    for (int i = size / 2 - 1; i >= 0; --i)
      heapifyDown(i);
  }

public:
  MaxHeap() : size{0}, capacity(1000), arr(new int[capacity]) {}
  MaxHeap(std::vector<int> &v) : MaxHeap() {

    assert((int)v.size() <= capacity);
    size = v.size();

    for (int i = 0; i < (int)v.size(); ++i)
      arr[i] = v[i];

    heapify();
  }
  ~MaxHeap() { delete[] arr; }

  int top() {
    assert(!isEmpty());
    return arr[0];
  }

  void push(int value) {
    arr[size++] = value;
    heapifyUp(size - 1);
  }

  void pop() {
    assert(!isEmpty());
    arr[0] = arr[size - 1];
    heapifyDown(0);
    --size;
  }

  bool isEmpty() { return size == 0; }
};
void creat_heap_nlogn() {
  MaxHeap heap;

  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

  for (int i = 0; i < (int)v.size(); ++i)
    heap.push(v[i]);

  while (!heap.isEmpty()) {
    std::cout << heap.top() << " ";
    heap.pop();
  }
}

void creat_heap_n() {
  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
  MaxHeap heap(v);

  // h.print();
  while (!heap.isEmpty()) {
    std::cout << heap.top() << " ";
    heap.pop();
  }
}

int main(int argc, char *argv[]) {
  // MaxHeap mxHeap;
  // mxHeap.push(1);
  // mxHeap.push(3);
  // mxHeap.push(10);
  // mxHeap.push(9);
  // mxHeap.push(8);
  // mxHeap.push(7);
  // mxHeap.push(5);
  // mxHeap.push(13);
  // mxHeap.push(11);
  // mxHeap.push(12);
  //
  // while (!mxHeap.isEmpty())
  //   std::cout << mxHeap.top() << ' ', mxHeap.pop();
  // std::cout << '\n';
  //

  creat_heap_nlogn();
  std::cout << '\n';
  creat_heap_n();
  std::cout << '\n';

  return 0;
}

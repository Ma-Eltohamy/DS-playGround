#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

class MinHeap {
private:
  int size, capacity, *arr;

  int getLeft(int rootIdx) {
    int left = {rootIdx * 2 + 1};

    if (left <= 0 || left >= size)
      return -1;
    return left;
  }

  int getRight(int rootIdx) {
    int right{rootIdx * 2 + 2};

    if (right <= 1 || right >= size)
      return -1;
    return right;
  }

  int getParent(int rootIdx) {
    int parent{(rootIdx - 1) / 2};

    if (rootIdx == 0 || parent < 0 || parent >= size)
      return -1;
    return parent;
  }

  void heapifyUp(int rootIdx) {
    int parent{getParent(rootIdx)};

    if (parent == -1 || arr[parent] < arr[rootIdx])
      return;

    std::swap(arr[parent], arr[rootIdx]);
    heapifyUp(parent);
  }

  void heapifyDown(int rootIdx) {
    int left{getLeft(rootIdx)};
    int right{getRight(rootIdx)};
    int mnChild{left};

    if (mnChild == -1 ||
        (mnChild != -1 && right != -1 && arr[mnChild] > arr[right]))
      mnChild = right;

    if (mnChild == -1 || arr[mnChild] > arr[rootIdx])
      return;

    std::swap(arr[mnChild], arr[rootIdx]);
    heapifyDown(mnChild);
  }

  void heapify() { // O(n)
    for (int i = size / 2 - 1; i >= 0; --i)
      heapifyDown(i);
  }

public:
  MinHeap() : size(0), capacity(1000), arr(new int[capacity]) {}
  ~MinHeap() { delete[] arr; }

  MinHeap(const std::vector<int> &v) {
    assert((int)v.size() <= capacity);
    arr = new int[capacity]{};
    size = v.size();

    for (int i = 0; i < (int)v.size(); ++i)
      arr[i] = v[i];

    heapify();
  }

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

class MaxHeap {
private:
  MinHeap heap;

  std::vector<int> multiplyNeg1(const std::vector<int> &v) {
    std::vector<int> res = v;
    for (int i = 0; i < (int)res.size(); ++i)
      res[i] *= -1;
    return res;
  }

public:
  MaxHeap() : heap() {}
  MaxHeap(const std::vector<int> &v) : heap(multiplyNeg1(v)) {}
  int top() { return -heap.top(); }
  void pop() { heap.pop(); }
  void push(int value) { heap.push(-value); }
  bool isEmpty() { return heap.isEmpty(); }
};

void creat_heap_nlogn() {
  MaxHeap heap;

  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

  for (int i = 0; i < v.size(); ++i)
    heap.push(v[i]);

  while (!heap.isEmpty()) {
    std::cout << heap.top() << " ";
    heap.pop();
  }
  // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
}

void creat_heap_n() {
  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
  MaxHeap heap(v);

  while (!heap.isEmpty()) {
    std::cout << heap.top() << " ";
    heap.pop();
  }
}

int main() {
  creat_heap_n();
  std::cout << '\n';
  creat_heap_nlogn();
  std::cout << '\n';

  return 0;
}

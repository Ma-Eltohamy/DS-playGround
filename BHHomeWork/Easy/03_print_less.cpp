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

  void _printLessThan(int val, int curIdx) {
    if (arr[curIdx] >= val)
      return;

    std::cout << arr[curIdx] << ' ';
    int left{getLeft(curIdx)};
    int right{getRight(curIdx)};
    if (left != -1)
      _printLessThan(val, left);
    if (right != -1)
      _printLessThan(val, right);
  }

  void printLessThan(int val) {
    if (top() >= val)
      return;
    _printLessThan(val, 0);
  }

  bool isEmpty() { return size == 0; }
};
void creat_heap_nlogn() {
  MinHeap heap;

  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

  for (int i = 0; i < (int)v.size(); ++i)
    heap.push(v[i]);

  heap.printLessThan(10); // 2 5 8 6 7
  std::cout << "\n";

  // h.print();
  // while (!heap.isEmpty()) {
  //   std::cout << heap.top() << " ";
  //   heap.pop();
  // }
}

int main() {
  creat_heap_nlogn();
  return 0;
}

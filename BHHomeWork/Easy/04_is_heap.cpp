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

  bool isHeapArray(int *arr, int n) {
    int oldSize = size; // To make getLeft& getRight work well
    size = n;

    bool isHeap{true};
    int left{}, right{};

    n = (n - 1) / 2; // To loop on only parent node

    for (int i = 0; i < n; ++i) {
      left = getLeft(i);
      right = getRight(i);
      if (arr[i] > arr[left] || arr[i] > arr[right]) {
        isHeap = false;
        break;
      }
    }
    size = oldSize;
    return isHeap;
  }

  // bool isHeap(int *arr, int rootIdx) {
  //   if (rootIdx == -1)
  //     return true;
  //
  //   int left{getLeft(rootIdx)}, right{getRight(rootIdx)};
  //
  //   if ((left != -1 && arr[rootIdx] > arr[left]) ||
  //       (right != -1 && arr[rootIdx] > arr[right]))
  //     return false;
  //
  //   return isHeap(arr, left) && isHeap(arr, right);
  // }
  // bool isHeapArray(int *arr, int n) {
  //   int oldSize = size;
  //   size = n;
  //   bool res{isHeap(arr, 0)};
  //   size = oldSize;
  //   return res;
  // }

  bool isEmpty() { return size == 0; }
};
void is_heap_array() {
  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
  MinHeap heap(v);

  int arr[]{2, 5, 12, 7, 6, 22, 14, 19, 10, 17, 8, 37, 25, 30};
  int arr1[]{2, 4, 3, 5, 10};
  int arr2[]{7, 9, 8, 10};
  int arr3[]{1, 4};
  int arr4[]{10, 5, 6, 4, 8, 11};
  std::cout << heap.isHeapArray(arr, 14) << "\n"; // 1
  std::swap(arr[0], arr[5]);
  std::cout << heap.isHeapArray(arr, 14) << "\n"; // 0

  std::cout << heap.isHeapArray(arr1, 5) << "\n"; // 1
  std::cout << heap.isHeapArray(arr2, 4) << "\n"; // 1
  std::cout << heap.isHeapArray(arr3, 2) << "\n"; // 1
  std::cout << heap.isHeapArray(arr4, 6) << "\n"; // 0
}

int main() {
  is_heap_array();

  return 0;
}

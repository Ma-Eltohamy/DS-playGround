#include <iostream>
#include <utility>
#include <vector>

void heapifyDown(std::vector<int> &v, int rootIdx, int vecSize) {
  int leftIdx{rootIdx * 2 + 1};
  int rightIdx{rootIdx * 2 + 2};
  int minIdx{rootIdx};

  // Get min Child
  // If we changed only the second operator (It change from min \ max)
  //                                  |
  //                                  |
  if (leftIdx < vecSize && v[leftIdx] > v[minIdx])
    minIdx = leftIdx;
  if (rightIdx < vecSize && v[rightIdx] > v[minIdx])
    minIdx = rightIdx;

  if (minIdx != rootIdx) {
    std::swap(v[minIdx], v[rootIdx]);
    heapifyDown(v, minIdx, vecSize);
  }
}
void heapSort(std::vector<int> &v) {
  int vecSize{(int)v.size()};

  // Build heap for the frist time
  for (int i = vecSize; i >= 0; --i)
    heapifyDown(v, i, vecSize);

  // Then
  --vecSize;
  for (; vecSize; --vecSize) {
    std::swap(v[0], v[vecSize]);
    heapifyDown(v, 0, vecSize);
  }
}

void print(std::vector<int> &v) {
  int vecSize{(int)v.size()};
  for (int i = 0; i < vecSize; ++i)
    std::cout << v[i] << ' ';
  std::cout << '\n';
}
int main(int argc, char *argv[]) {
  std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

  print(v);
  heapSort(v);
  print(v);
  return 0;
}

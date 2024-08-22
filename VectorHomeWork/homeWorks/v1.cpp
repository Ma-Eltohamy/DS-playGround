#include <assert.h>
#include <climits>
#include <iostream>
#include <utility>

class Vector {
private:
  int *arr = nullptr;
  int size{0};
  int capacity{0};

public:
  Vector(int size) : size(size), capacity(size) {
    if (size < 0)
      size = 1;
    arr = new int[capacity];
  }

  int get(int idx) const {
    assert(0 <= idx && idx < size);
    return arr[idx];
  }
  int &operator[](int idx) const {
    assert(0 <= idx && idx < size);
    return arr[idx];
  }
  void set(int idx, int value) {
    assert(0 <= idx && idx < size);
    arr[idx] = value;
  }

  int find(int value) const {
    for (int i = 0; i < size; ++i)
      if (arr[i] == value)
        return i;
    return -1;
  }

  int getSize() const { return size; }

  void print() const {
    for (int i = 0; i < size; ++i)
      std::cout << arr[i] << ' ';
    std::cout << std::endl;
  }

  int getFront(int value) const { return arr[0]; }
  int getBack(int value) const { return arr[size - 1]; }

  void expandCapacity(int idx = -1) {
    do {
      capacity *= 2;
    } while (idx >= capacity);

    int *other = new int[capacity];

    for (int i = 0, j = 0; i < size; ++i, ++j) {
      if (idx == j)
        ++j; // skip
      other[j] = arr[i];
    }

    std::swap(arr, other);
    delete[] other;
    other = nullptr;
  }

  void pushBack(int value) {
    if (capacity == size) {
      expandCapacity();
    }

    arr[size++] = value;
  }

  void pushFront(int value) {
    if (capacity == size)
      expandCapacity(0);
    else
      shiftRight(0);
    arr[0] = value;
    ++size;
  }

  void shiftRight(int idx) {
    for (int i = size - 1; i >= idx; --i)
      arr[i + 1] = arr[i];
  }

  void insert(int idx, int value) {
    assert(0 <= idx && idx < INT_MAX);

    if (idx >= capacity) { // out of capacity
      expandCapacity(idx);
      size = idx + 1;
    } else {
      shiftRight(idx);
      ++size;
    }
    arr[idx] = value;
  }

  // Adding Right Rotation Function
  void rightRotate() {
    int last = arr[size - 1];
    for (int i = size - 1; i >= 1; --i)
      arr[i] = arr[i - 1];
    arr[0] = last;
  }

  ~Vector() {
    delete[] arr;
    arr = nullptr;
  }
};

int main(int argc, char *argv[]) {
  Vector v(5);
  for (int i = 0; i < 5; ++i)
    v.set(i, i);

  v.print();

  v.rightRotate();
  v.print();

  return 0;
}

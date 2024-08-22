#include "vector.hpp"
#include <cassert>
#include <climits>
#include <iostream>

Vector::Vector(int size) : size(size), capacity(size) {
  if (size < 0)
    size = 1;
  arr = new int[capacity];
}

int Vector::get(int idx) const {
  assert(0 <= idx && idx < size);
  return arr[idx];
}
int &Vector::operator[](int idx) const {
  assert(0 <= idx && idx < size);
  return arr[idx];
}
void Vector::set(int idx, int value) {
  assert(0 <= idx && idx < size);
  arr[idx] = value;
}

int Vector::find(int value) const {
  for (int i = 0; i < size; ++i)
    if (arr[i] == value)
      return i;
  return -1;
}

int Vector::getSize() const { return size; }

void Vector::print() const {
  for (int i = 0; i < size; ++i)
    std::cout << arr[i] << ' ';
  std::cout << std::endl;
}

int Vector::getFront(int value) const { return arr[0]; }
int Vector::getBack(int value) const { return arr[size - 1]; }

void Vector::expandCapacity(int idx = -1) {
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

void Vector::pushBack(int value) {
  if (capacity == size) {
    expandCapacity();
  }

  arr[size++] = value;
}

void Vector::pushFront(int value) {
  if (capacity == size)
    expandCapacity(0);
  else
    shiftRight(0);
  arr[0] = value;
  ++size;
}

void Vector::shiftRight(int idx) {
  for (int i = size - 1; i >= idx; --i)
    arr[i + 1] = arr[i];
}

void Vector::insert(int idx, int value) {
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

Vector::~Vector() {
  delete[] arr;
  arr = nullptr;
};

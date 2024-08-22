#pragma once
class Vector {
private:
  int *arr{nullptr};
  int size{0};
  int capacity{0};
  void expandCapacity(int idx);
  void shiftRight(int idx);

public:
  Vector(int size);

  int get(int idx) const;
  int &operator[](int idx) const;
  void set(int idx, int value);
  int find(int value) const;
  int getSize() const;
  void print() const;
  int getFront(int value) const;
  int getBack(int value) const;

  void pushBack(int value);
  void pushFront(int value);
  void insert(int idx, int value);
  ~Vector();
};

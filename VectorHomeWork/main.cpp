#include "vector.hpp"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

  std::vector<int> vv;
  Vector v(10);
  for (int i = 0; i < v.getSize(); ++i)
    v.set(i, i);

  v.print();
  std::cout << v.find(5) << ' ' << v.find(55) << std::endl;
  std::cout << v.getSize() << std::endl;

  for (int i = 0; i < 9000000; ++i)
    v.pushBack(i);

  v.pushBack(10);
  std::cout << v.getSize() << std::endl;
  v.print();

  v.pushFront(992);
  std::cout << v.getSize() << std::endl;
  v.print();

  v.insert(4, 997979);
  v.print();

  v.insert(100, 111);
  v.print();

  for (int i = 0; i < 1000000; ++i)
    v.pushBack(i);
  v.print();

  return 0;
}

#include <iostream>

class Stack {
private:
  int size{};
  int addedElements{};
  int *array{};

public:
  Stack(int size) : size(size), array(new int[size]) {}

  bool shiftRight() { // O(n) time O(1) memory
    if (!array || isFull())
      return false;

    for (int i = addedElements - 1; i >= 0; --i)
      array[i + 1] = array[i];

    return true;
  }

  bool shiftLeft() { // O(n) time O(1) memory
    if (!array)
      return false;

    for (int i = 0; i < addedElements; ++i)
      array[i] = array[+1];

    return true;
  }

  bool push(int value) { // O(n) time O(1) memory
    if (shiftRight()) {
      array[0] = value;
      ++addedElements;
      return true;
    }
    return false;
  }

  bool pop(int &result) { // O(n) time O(1) memroy
    if (isEmpty())
      return false;

    result = array[0];
    if (shiftLeft()) {
      --addedElements;
      return true;
    }
    return false;
  }

  bool peek(int &result) { // O(n) time O(1) memory
    if (isEmpty())
      return false;
    result = array[0];
    return true;
  }

  bool isFull() { return (addedElements == size); }
  bool isEmpty() { return (addedElements == 0); }

  void display() {
    for (int i = 0; i < addedElements; ++i)
      std::cout << array[i] << ' ';
    std::cout << std::endl;
  }

  ~Stack() { delete[] array; }
};
int main(int argc, char *argv[]) {

  Stack stk(3);
  stk.push(10);
  stk.push(20);
  stk.push(30);

  if (!stk.push(50))
    std::cout << "Full Stack\n";

  stk.display(); // 30 20 10
  int result;
  if (stk.peek(result))
    std::cout << result << "\n"; // 30

  while (stk.pop(result)) {
    std::cout << result << " ";
  } // 30 20 10

  return 0;
}

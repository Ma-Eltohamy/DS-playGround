#include <iostream>
#include <stack>

class Queue {
private:
  int size{};
  int addedEelements{};
  std::stack<int> s1;
  std::stack<int> s2;

public:
  Queue(int size) : size(size) {}
  void moveElements(std::stack<int> &fromStack, std::stack<int> &toStack) {
    while (!fromStack.empty())
      toStack.push(fromStack.top()), fromStack.pop();
  }
  void enqueue(int value) {
    moveElements(s2, s1);
    s1.push(value);
    moveElements(s1, s2);
    ++addedEelements;
  }
  int dequeue() {
    int tmp = s2.top();
    s2.pop();
    --addedEelements;
    return tmp;
  }
  bool isEmpty() { return addedEelements == 0; }
};
int main(int argc, char *argv[]) {
  // some operations
  Queue qu(6);

  for (int i = 1; i <= 3; ++i)
    qu.enqueue(i);

  std::cout << qu.dequeue() << " ";

  for (int i = 4; i <= 5; ++i)
    qu.enqueue(i);

  while (!qu.isEmpty())
    std::cout << qu.dequeue() << " ";
  return 0;
}

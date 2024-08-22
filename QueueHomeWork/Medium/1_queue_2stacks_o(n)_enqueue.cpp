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
    moveElements(s1, s2);
    s2.push(value);
    moveElements(s2, s1);
    ++addedEelements;
  }
  // Here we can't apply if(s1.empty()) because
  // What if i want to delete them all
  // i don't want even at the last element the dequeue function to be o(n)
  int dequeue() {
    int tmp = s1.top();
    s1.pop();
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
